# SPDX-License-Identifier: Apache-2.0

if(CONFIG_BOARD_ALERTRAX60_NRF9160_NS OR CONFIG_BOARD_ALERTRAX61_NRF9161_NS OR CONFIG_BOARD_ALERTRAX51_NRF9151_NS)
  set(TFM_PUBLIC_KEY_FORMAT "full")
endif()

if(CONFIG_TFM_FLASH_MERGED_BINARY)
  set_property(TARGET runners_yaml_props_target PROPERTY hex_file tfm_merged.hex)
endif()

if(CONFIG_SOC_NRF9160_SICA)
  board_runner_args(jlink "--device=nRF9160_xxAA" "--speed=4000")
endif()

# TODO: change to nRF9151_xxAA when such device is available in JLink
if(CONFIG_SOC_NRF9151_LACA)
  board_runner_args(jlink "--device=nRF9151_xxCA" "--speed=4000")
endif()

# TODO: change to nRF9161_xxAA when such device is available in JLink
if(CONFIG_SOC_NRF9161_LACA)
  board_runner_args(jlink "--device=nRF9161_xxCA" "--speed=4000")
endif()
include(${ZEPHYR_BASE}/boards/common/nrfjprog.board.cmake)
include(${ZEPHYR_BASE}/boards/common/nrfutil.board.cmake)
include(${ZEPHYR_BASE}/boards/common/jlink.board.cmake)
