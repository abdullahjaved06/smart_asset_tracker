


#include "max25r16.h"


LOG_MODULE_REGISTER(Flash);

#define MAX_OPEN_FILES 6

struct FS_STRUCT {
	int file_handle;
	struct fs_file_t file;
	bool open;
};

struct FS_STRUCT file_system_array[MAX_OPEN_FILES];

K_MUTEX_DEFINE(fs_lock);

/* Matches LFS_NAME_MAX */
#define MAX_PATH_LEN 255

const struct device *flash_dev = DEVICE_DT_GET(DT_NODELABEL(mx25r16));

/* Config */
struct system_config {
	int32_t update_interval;
	int32_t status;
};

static struct system_config cfg = {
	.update_interval = 0,
	.status = 0,
};

int BOOT_COUNT = 0;
bool FLASH_ENABLED = false;

#define MNT_POINT "/lfs"

FS_LITTLEFS_DECLARE_DEFAULT_CONFIG(storage);
static struct fs_mount_t lfs_storage_mnt = {
	.type = FS_LITTLEFS,
	.fs_data = &storage,
	.storage_dev = (void *)FLASH_AREA_ID(littlefs_storage),
	.mnt_point = MNT_POINT,
};

struct fs_mount_t *logMP = &lfs_storage_mnt;
struct fs_file_t logFile;

static const char *LOG_FILENAME_PATH = MNT_POINT "/debug.log";
static const char *CLOUD_DATA_FILENAME_PATH = MNT_POINT "/cloud_data.data";

static int test_settings_set(const char *name, size_t len, settings_read_cb read_cb, void *cb_arg)
{
	const char *next;
	int rc;

	if (settings_name_steq(name, "entry", &next) && !next) {
		if (len != sizeof(cfg)) {
			return -EINVAL;
		}

		rc = read_cb(cb_arg, &cfg, sizeof(cfg));
		if (rc >= 0) {
			/* key-value pair was properly read.
			 * rc contains value length.
			 */
			return 0;
		}
		/* read-out error */
		return rc;
	}

	return -ENOENT;
}

struct settings_handler my_config = {
	.name = "config",
	.h_set = test_settings_set,
};

int readlnFS(struct fs_file_t *file, char *buf, size_t size)
{
	int i = 0;
	while (i < size) {
		int read = fs_read(file, &buf[i], 1);
		if (read < 1) {
			break;
		}
		if (buf[i] == '\n') {
			i++;
			break;
		}
		i++;
	}
	buf[i] = '\0';
	return i;
}

int writelnFS(struct fs_file_t *file, char *buf)
{
	int write = 0;
	if (buf != NULL)
		write = fs_write(file, buf, strlen(buf));

	return write;
}

int unlinkFlashFile(const char *filename)
{
	char fname[MAX_PATH_LEN];

	snprintf(fname, sizeof(fname), "%s/%s", logMP->mnt_point, filename);
	return fs_unlink(fname);
}

// Init, Suspend and Resume MUST be done before this function
int openFlashFile(const char *filename)
{
	int i = 0;
	int file_handle = -1;
	char fname[MAX_PATH_LEN];

	k_mutex_lock(&fs_lock, K_FOREVER);
	for (i = 0; i < MAX_OPEN_FILES; i++) {
		if (file_system_array[i].open == false) {
			file_handle = i;
			break;
		}
	}
	if (file_handle < 0) {
		LOG_ERR("No file handles available");
		goto out;
	}
	snprintf(fname, sizeof(fname), "%s/%s", logMP->mnt_point, filename);
	fs_file_t_init(&(file_system_array[file_handle].file));
	int rc = fs_open(&(file_system_array[file_handle].file), fname, FS_O_CREATE | FS_O_RDWR);
	if (rc < 0) {
		LOG_ERR("FAIL: open %s: %d\n", fname, rc);
		goto out;
	}

out:
	k_mutex_unlock(&fs_lock);
	return file_handle;
}

// Init, Suspend and Resume MUST be done before this function
int closeFlashFile(int file_handle)
{
	k_mutex_lock(&fs_lock, K_FOREVER);

	file_system_array[file_handle].open = false;
	int rc = fs_close(&(file_system_array[file_handle].file));

	k_mutex_unlock(&fs_lock);

	return rc;
}

ssize_t readBlockFS(int file_handle, void *buf, size_t size)
{
	return fs_read(&(file_system_array[file_handle].file), buf, size);
}

ssize_t writeBlockFS(int file_handle, void *buf, size_t size)
{
	int written = -1;

	if (buf != NULL)
		written = fs_write(&(file_system_array[file_handle].file), buf, size);
	return written;
}

int initFsLog(bool eraseLog)
{
	int rc = -1;
	unsigned int id = (uintptr_t)logMP->storage_dev;
	const struct flash_area *pfa;

	LOG_INF("Init Flash");
	for (int i = 0; i < MAX_OPEN_FILES; i++) {
		file_system_array[i].open = false;
	}

	rc = fs_mount(logMP);
	if (rc < 0) {
		printk("FAIL: mount: %d\n", rc);
		solidRedFlashingGreen(10, 500);
		goto out;
	}

	rc = flash_area_open(id, &pfa);
	if (rc < 0) {
		LOG_ERR("FAIL: unable to find flash area %u: %d\n", id, rc);
		goto out;
	}

	LOG_INF("Area %u at 0x%x for %u bytes\n", id, (unsigned int)pfa->fa_off,
		(unsigned int)pfa->fa_size);

	// Optional wipe flash contents
	// if (IS_ENABLED(CONFIG_APP_WIPE_STORAGE)) {
	if (eraseLog) {
		LOG_WRN("Erasing flash area ... ");
		rc = flash_area_erase(pfa, 0, pfa->fa_size);
		printk("%d\n", rc);
	}

	flash_area_close(pfa);

	BOOT_COUNT = bootCount();

	if (eraseLog) {
		fs_unlink(LOG_FILENAME_PATH);
	}

	LOG_INF("Log path is %s", LOG_FILENAME_PATH);
	FLASH_ENABLED = true;
out:
	suspendFlash();
	LOG_INF("Flash initialized");
	return rc;
}

int __printf_like(1, 2) writeFsLog(char *fmt, ...)
{
	int rc = -1;
#ifdef CONFIG_ALERTRAX_WITH_FILE_UPLOAD
	char buf[LOG_LEN] = {0};

	if (!FLASH_ENABLED)
		return rc;

	va_list args;
	va_start(args, fmt);
	int ret = vsnprintf(buf, LOG_LEN, fmt, args);
	va_end(args);
	if (ret < 0) {
		return ret;
	}

	int diff = ret - (LOG_LEN - 1);
	if (diff >= 0) {
		buf[LOG_LEN - 1] = '\n';
	} else {
		buf[ret] = '\n';
	}

	resumeFlash();

	fs_file_t_init(&logFile);
	rc = fs_open(&logFile, LOG_FILENAME_PATH, FS_O_CREATE | FS_O_APPEND | FS_O_WRITE);
	if (rc < 0) {
		LOG_ERR("FAIL: open %s: %d\n", LOG_FILENAME_PATH, rc);
		goto out;
	}

	rc = fs_write(&logFile, buf, strlen(buf));
	if (rc > 0) {
		fs_sync(&logFile);
	}

	fs_close(&logFile);

	printk("%s", buf);

out:
	suspendFlash();

#endif // CONFIG_ALERTRAX_WITH_FILE_UPLOAD
	return rc;
}

void printFsLog()
{
	if (!FLASH_ENABLED)
		return;

	char buf[2048];
	int rc;

	resumeFlash();

	fs_file_t_init(&logFile);
	rc = fs_open(&logFile, LOG_FILENAME_PATH, FS_O_READ);
	if (rc < 0) {
		LOG_ERR("FAIL: open %s: %d\n", LOG_FILENAME_PATH, rc);
		goto out;
	}

	printk("** LOG OUTPUT **\n");
	fs_seek(&logFile, 0, FS_SEEK_SET);
	memset(buf, 0, sizeof(buf));
	while (fs_read(&logFile, &buf, sizeof(buf)) > 0) {
		printk("%s", buf);
		memset(buf, 0, sizeof(buf));
	}
	printk("**** BOOT COUNT: %d **\n", BOOT_COUNT);
	printk("**** LOG END **\n");

out:
	suspendFlash();
}

void resetFsLog()
{
#ifdef CONFIG_ALERTRAX_WITH_FILE_UPLOAD
	if (!FLASH_ENABLED)
		return;

	resumeFlash();
	int rc;
	for (int i = 0; i < 5; i++) {
		rc = fs_unlink(LOG_FILENAME_PATH);
		if (rc == 0) {
			break;
		}
	}
	if (rc) {
		LOG_ERR("Failed to delete log file, error: %d", rc);
		writeFsLog("Failed to delete log file, error: %d", rc);
	} else {
		LOG_INF("Log file deleted");
	}
	suspendFlash();
#endif // CONFIG_ALERTRAX_WITH_FILE_UPLOAD
}

ssize_t getFsLogChunk(size_t offset, char *out_buffer, size_t max_size)
{
	resumeFlash();
	int err;
	struct fs_file_t file;
	fs_file_t_init(&file);
	ssize_t read = -1;

	err = fs_open(&file, LOG_FILENAME_PATH, FS_O_READ);
	if (err) {
		LOG_ERR("Failed to open file %s: %d", LOG_FILENAME_PATH, err);
		goto cleanup;
	}
	err = fs_seek(&file, offset, FS_SEEK_SET);
	if (err) {
		LOG_ERR("Failed to seek file");
		goto cleanup;
	}

	read = fs_read(&file, out_buffer, max_size);
	if (read < 0) {
		LOG_ERR("Failed to read file");
		goto cleanup;
	}

cleanup:
	fs_close(&file);
	suspendFlash();
	return read;
}

size_t getFsLogSize(void)
{
	resumeFlash();
	struct fs_dirent entry;
	int err;
	err = fs_stat(LOG_FILENAME_PATH, &entry);
	suspendFlash();

	return (err == 0) ? entry.size : 0;
}

int closeLog()
{
	int rc;
	rc = fs_close(&logFile);
	rc = fs_unmount(logMP);
	return rc;
}

int bootCount(void)
{
	char fname[MAX_PATH_LEN];
	int rc;
	uint32_t boot_count = 0;
	struct fs_file_t file;

	snprintf(fname, sizeof(fname), "%s/boot_count", logMP->mnt_point);

	fs_file_t_init(&file);
	rc = fs_open(&file, fname, FS_O_CREATE | FS_O_RDWR);
	if (rc < 0) {
		LOG_ERR("FAIL: open %s: ", fname);
		switch (rc) {
		case -EBUSY:
			LOG_ERR("EBUSY");
			break;
		case -EINVAL:
			LOG_ERR("EINVAL");
			break;
		case -EROFS:
			LOG_ERR("EROFS");
			break;
		case -ENOENT:
			LOG_ERR("ENOENT");
			break;
		case -ENOTSUP:
			LOG_ERR("ENOTSUP");
			break;
		default:
			LOG_ERR("Unknown error");
		}
		goto out;
	}

	if (rc >= 0) {
		rc = fs_read(&file, &boot_count, sizeof(boot_count));
		// printk("%s read count %u: %d\n", fname, boot_count, rc);
		rc = fs_seek(&file, 0, FS_SEEK_SET);
		// printk("%s seek start: %d\n", fname, rc);
	}

	boot_count += 1;
	LOG_INF("Boot count: %d", boot_count);
	rc = fs_write(&file, &boot_count, sizeof(boot_count));
	// printk("%s write new boot count %u: %d\n", fname, boot_count, rc);

	rc = fs_close(&file);
	// printk("%s close: %d\n", fname, rc);

	/* Using settings subsystem */
	/*
		settings_subsys_init();
		settings_register(&my_config);
		settings_load();

		printk("Settings: before: status %i, interval: %i\n", cfg.status,
	   cfg.update_interval);

		cfg.status += 1;
		cfg.update_interval = 20;

		printk("Settings: after: status %i, interval: %i\n", cfg.status,
	   cfg.update_interval);

		settings_save_one("config/entry", &cfg, sizeof(cfg));
	*/

	/* End of setting related items */

out:
	// rc = fs_unmount(mp);
	// printk("%s unmount: %d\n", mp->mnt_point, rc);
	return boot_count;
}

void suspendFlash()
{

	if (device_is_ready(flash_dev))
		pm_device_action_run(flash_dev, PM_DEVICE_ACTION_SUSPEND);
}

void resumeFlash()
{

	if (device_is_ready(flash_dev))
		pm_device_action_run(flash_dev, PM_DEVICE_ACTION_RESUME);
}

bool cloudDataFileExists(void)
{
	if (!FLASH_ENABLED)
		return false;

	resumeFlash();
	struct fs_dirent entry;
	int err = fs_stat(CLOUD_DATA_FILENAME_PATH, &entry);
	suspendFlash();
	return (err == 0);
}

int cloudDataFileWrite(const void *src, uint32_t len, uint32_t offset)
{
	int ret = 1;

	if (!FLASH_ENABLED)
		return ret;

	resumeFlash();

	struct fs_file_t cloudFile;
	fs_file_t_init(&cloudFile);
	int rc = fs_open(&cloudFile, CLOUD_DATA_FILENAME_PATH, FS_O_CREATE | FS_O_WRITE);
	if (rc < 0) {
		LOG_ERR("FAIL: open %s: %d\n", CLOUD_DATA_FILENAME_PATH, rc);
		goto end;
	}

	rc = fs_seek(&cloudFile, offset, FS_SEEK_SET);
	if (rc < 0) {
		LOG_ERR("FAIL: seek %s: %d\n", CLOUD_DATA_FILENAME_PATH, rc);
		goto end;
	}

	rc = fs_write(&cloudFile, src, len);
	if (rc != len) {
		LOG_ERR("FAIL: write %s: %d\n", CLOUD_DATA_FILENAME_PATH, rc);
		goto end;
	}

	fs_sync(&cloudFile);

	ret = 0;
end:
	fs_close(&cloudFile);
	suspendFlash();
	return ret;
}

int cloudDataFileRead(void *dst, uint32_t len, uint32_t offset)
{
	int ret = 1;

	if (!FLASH_ENABLED)
		return ret;

	resumeFlash();

	struct fs_file_t cloudFile;
	fs_file_t_init(&cloudFile);
	int rc = fs_open(&cloudFile, CLOUD_DATA_FILENAME_PATH, FS_O_READ);
	if (rc < 0) {
		LOG_ERR("FAIL: open %s: %d\n", CLOUD_DATA_FILENAME_PATH, rc);
		goto end;
	}

	rc = fs_seek(&cloudFile, offset, FS_SEEK_SET);
	if (rc < 0) {
		LOG_ERR("FAIL: seek %s: %d\n", CLOUD_DATA_FILENAME_PATH, rc);
		goto end;
	}

	rc = fs_read(&cloudFile, dst, len);
	if (rc != len) {
		LOG_ERR("FAIL: read %s: %d\n", CLOUD_DATA_FILENAME_PATH, rc);
		goto end;
	}

	ret = 0;
end:
	fs_close(&cloudFile);
	suspendFlash();
	return ret;
}

void cloudDataFileDelete(void)
{
	if (!FLASH_ENABLED)
		return;

	resumeFlash();
	if (fs_unlink(CLOUD_DATA_FILENAME_PATH)) {
		LOG_ERR("Failed to delete cloud data file");
	}
	suspendFlash();
}