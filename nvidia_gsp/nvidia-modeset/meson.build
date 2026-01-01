shared_library('nvidia_gsp_modeset',
	'nvkms-haiku.cpp',
	'KmsDriver.cpp',
	'KmsDevice.cpp',
	'TimerQueue.cpp',
	include_directories: [
		'..',

		'/boot/system/develop/headers/private',
		'/boot/system/develop/headers/private/shared',
		'/boot/system/develop/headers/private/kernel',
		'/boot/system/develop/headers/private/kernel/arch/x86',
		'/boot/system/develop/headers/private/kernel/arch/x86/64',
		'/boot/system/develop/headers/private/system',
		'/boot/system/develop/headers/private/system/arch/x86_64',
		'/boot/system/develop/headers/private/kernel/boot/platform/efi',
	],
	link_whole: [
		lib_nvhaiku_common,
	],
	dependencies: [
		dep_nvrm,
		dep_nv_modeset_kernel,
		dep_nvkms,
	],
	name_prefix: '',
	name_suffix: '',
	gnu_symbol_visibility: 'hidden',
	install: true,
	install_dir: 'add-ons/kernel/drivers/bin',
)

install_symlink('nvidia_gsp_modeset', pointing_to: '../bin/nvidia_gsp_modeset', install_dir: 'add-ons/kernel/drivers/dev')
