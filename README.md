# SM8150 Mainline Linux — Google Pixel 4 (google-flame)

This repository contains build automation and provenance for Linux on the Snapdragon 855 / SM8150 Google Pixel 4. The full kernel source remains in the upstream SM8150 project and is mirrored into `upstream/*` branches by GitHub Actions.

## Tracks

- **Device-support baseline:** SM8150-specific kernel source and Pixel 4 DTB. Default ref is `v6.17.0-sm8150`; always review the source manifest.
- **Latest stable experiment:** `build-latest-stable.yml` resolves and verifies the current stable kernel.org tarball, merges the SM8150 config fragment, overlays the Pixel 4 DTS, and attempts to build Image/modules/DTB. This is an experiment, not a device-validated kernel; older downstream patches and device-specific drivers are not automatically ported.
- **Upstream mirror:** preserves upstream branches/tags in this repo without overwriting our `main` branch.

## Actions

1. Run **Mirror SM8150 Mainline source to GitHub** once.
2. Run **Build SM8150 device-support kernel** with the known SM8150 device-support ref.
3. Run **Build latest stable upstream kernel (experimental)** separately.

Build artifacts include kernel Image, Pixel 4 DTB, config, System.map, module archive, Wi-Fi/Bluetooth kernel-config audit, manifests and SHA-256 sums. The device-support build attempts to enable CFG80211/MAC80211, ath10k SNOC, Bluetooth QCA UART, QRTR, and compressed firmware support where those symbols exist in the selected source. Review `wifi-bluetooth-kernel-config.txt`; requested Kconfig symbols can be removed by `olddefconfig` when dependencies or source support are absent. Nothing in these workflows flashes a phone.

## Device and recovery safety

The supplied phone layout reports physical `super` size `0x245800000` bytes (about 9.1 GiB), current slot B, and slot A marked unbootable. Fastboot's missing `system_a`/other A-side size variables do **not** prove an A-side logical partition is safe to overwrite. Obtain and inspect `lpdump` metadata in fastbootd/Android before resizing dynamic partitions.

Never flash a standalone ext4 rootfs image to the physical `super` block device. Android `super` contains LP metadata and logical partitions. To use it, create a dedicated logical partition only after calculating free extents and saving a verified restore path. Keep `userdata` untouched. A recoverable plan needs a backup of the original LP metadata and every partition that might be modified, plus a tested way to restore them.

## Upstream

- Kernel source: https://gitlab.postmarketos.org/soc/qualcomm-sm8150/linux
- Arch Linux ARM generic AArch64 rootfs: https://archlinuxarm.org/platforms/armv8/generic
- U-Boot Qualcomm-phone documentation: https://docs.u-boot-project.org/en/latest/board/qualcomm/phones.html

A successful CI build demonstrates compilation only. Hardware boot and peripheral support must be verified on the physical Pixel 4.
