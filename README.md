# minix-for-the-PT68K-2-4

🧠 PT68K MINIX 1.4 SD-Card/XT-IDE Boot and Disk Driver<br>
Author: Michael Evenson<br>
Target System: Peripheral Technology PT68K (Motorola 68000-based)<br>
Operating System: MINIX 1.4/68K<br>
Date: 2025<br>
License: Historical/Preservation Use<br>

1. Overview<br>
This project modernizes the Peripheral Technology PT68K single-board computer to run MINIX 1.4/68K entirely from a solid-state SD card, replacing traditional hard disks while maintaining full compatibility with the original HUMBUG monitor ROM and SK*DOS boot conventions.
A custom block device driver and bootstrap loader were written to achieve this, allowing the unmodified HUMBUG firmware to boot MINIX as though it were SK*DOS — seamlessly integrating modern storage into a vintage 68000 computing environment.

2. System Components<br>
ComponentDescriptionCPUMotorola MC68000Bus8-bit ISA compatibleFirmwareHUMBUG monitor ROM (unmodified)RTCBattery-backed Mostek MK48T02 (or equivalent)Mass StorageSD card via IDE-to-SD adapterInterfacePeripheral Technology XT-IDE 8-bit ISA cardOperating SystemMINIX 1.4/68K

3. Design Goals<br>
    Boot MINIX directly from an SD card with no modifications to HUMBUG.<br>
    Retain compatibility with SK*DOS boot protocols.<br>
    Integrate with the existing MINIX block device layer.<br>
    Preserve date/time across reboots using the PT68K’s battery-backed RTC.<br>
    Achieve full stability and transparency — the system behaves exactly as a traditional PT68K with an MFM or RLL disk.<br>

4. Boot Process<br>

    4.1 Standard HUMBUG behavior<br>
    HUMBUG expects to find an SK*DOS-style boot sector on the first disk track.<br>
    It reads the sector, loads additional blocks, and transfers control to the SK*DOS loader.<br>
    
    4.2 Custom loader design<br>
    The custom boot sector written for this project mimics SK*DOS, allowing HUMBUG to perform its normal SKDOS load sequence.<br>
    However, instead of launching SKDOS, the sector chain actually loads the MINIX secondary loader into memory.<br>
    From HUMBUG’s perspective, it has just booted SK*DOS.<br>
    In reality, it’s now executing the MINIX boot sequence.<br>
    
    4.3 Integration into HUMBUG ROM<br>
    Once verified, the loader’s logic was provided to Peripheral Technology, who incorporated the code directly into a later build of HUMBUG — giving the ROM native MINIX boot capability.<br>

5. Disk Driver<br>
    5.1 Architecture<br>
        The disk driver was implemented within MINIX’s standard block device layer (driver/hd.c equivalent).<br>
        It communicates with the XT-IDE registers in PIO mode (Programmed I/O), emulating standard MINIX block device semantics.<br>

    5.2 Interface<br>
        The driver exposes /dev/hd0, /dev/hd1, etc.<br>
        It supports read/write block operations using 512-byte sectors.<br>
        All access is handled synchronously via XT-IDE data and command ports mapped to the PT68K’s ISA address space.<br>

    5.3 SD Card Adaptation<br>
        The underlying storage is an SD card presented as an IDE device using a common IDE-to-SD adapter.<br>
        This allows the card to appear as a standard ATA drive, compatible with XT-IDE firmware and the driver’s existing ATA command set.<br>

6. RTC Integration<br>
The PT68K hardware includes a battery-backed Mostek RTC/NVRAM, which stores both clock and small configuration data.<br>

The MINIX kernel’s clock.c driver was modified to:<br>
    Read the RTC at boot (rtodc())<br>
    Write the RTC when date updates the system time (wtodc())<br>

This allows the system time to persist across reboots — unlike most early MINIX 1.x systems.<br>

7. Usage Summary<br>
TaskCommand/ProcedureCheck current date/timedateSet date/timedate MMDDYYhhmmssBoot MINIX from HUMBUGBO (standard HUMBUG boot command)SD Card replacementPower off → swap SD → reboot (fully supported)<br>
The MINIX loader and kernel both reside on the SD card’s first partition, which follows standard MINIX 1.x filesystem layout.<br>

8. Technical Highlights<br>
    Complete hardware compatibility with legacy PT68K systems<br>
    Full SK*DOS boot emulation<br>
    Clean integration with MINIX’s block I/O subsystem<br>
    No ROM modifications required for operation (original version)<br>
    Later versions incorporated boot code directly in HUMBUG<br>
    True persistent clock support under MINIX 1.4<br>
    Dramatically improved reliability and performance over MFM drives<br>

9. Historical Note<br>
This work preserves the spirit of the PT68K — a Motorola 68K development system that bridged the gap between hobbyist and professional computing — while modernizing it for practical use in the 21st century.<br>
By combining period-accurate architecture with modern storage, the PT68K MINIX 1.4 SD/IDE boot environment ensures that both the hardware and software legacy of the system remain operational and accessible to future generations.<br>

10. Files (recommended structure for distribution)<br>
PT68K_MINIX_SD/<br>
├── README.md<br>
├── boot/<br>
│   ├── skdos_compatible_boot.asm<br>
│   ├── minix_loader.asm<br>
│   └── humbug_integration_notes.txt<br>
├── driver/<br>
│   ├── xtide_hd.c<br>
│   └── xtide_hd.h<br>
├── images/<br>
│   ├── minix_sd_boot.img<br>
│   └── humbug_rom_with_minix_boot.bin<br>
└── docs/<br>
    ├── hardware_notes.md<br>
    ├── build_instructions.md<br>
    └── changelog.txt<br>

---------End of Chat GPT generated Read.me file ------------------------------------

This is the minix version 1.4b distribution I have been working on for the Peripheral Technology PT68K-2 and PT68K-4 compulters.<br>

    hd1.zip has the files that will end up in the root<br>
    hd2.aip has the files that will be mounted as usr<br>
    hd3.zip has the files that will be mounted as usr2 <- this is where the active source is located<br>

Support for the PT XT-IDE controller has been added and the WD1002-WX1 has been removed. The code is still there, I just replaced the device in the devices table.

I have also semi-recreated emacs version 3.9p+ that was written for the PT68K-2/4 minix machines. Somewhere down the line, the source got lost and I have attempted to recreate it from the 3.7 sources that were on the hard drive when I aquired it. I think I got all of the functionality from the emacs executable that is in the usr/bin directory. My compilation is called umacs in usr/bin. I kept the original sources in the usr2/src/minix/commands/emacs directory in a directory under that called 'original'. The modifications I made are in the usr2/src/minix/commands/emacs directory. Once I got umacs working the same as the emacs executable in the /usr/bin directory, I started making some customizations to remove some of the annoying requirements in 3.9p+. I call my version 3.9pt68k. The things I added/changed are:

  cursor control keys have been augmented to allow control and shift operations on them. Here is a description of the changes:

      1.  shift right arrow  - drop a mark and start moving the cursor to the right  (only on keypad)
      2.  shift left  arrow  - drop a mark and start moving the cursor to the left   (only on keypad)
      3.  shift down           drop a mark and start moving the cursor down one line (only on keypad)
      4.  shift up             drop a mark and start moving the cursor up one line   (only on keypad)
      5.  control right arrow  move the cursor right one word
      6.  control left  arrow  move the cursor left  one word
      7.  shift Insert         same as ^Y - yank the kill buffer to the cursor position
      8.  control Insert       same as M-W - copy region marked
      9.  Home now goes to the start of the current line
      10. End now goes to the end of the line
      11. control Home goes to the beginning of the file
      12. control End goes to the end of the file

The changes I made to the kernel to support these emacs changes are primarily in the ebind.h etype.h basic.c and ptkbd.c files. I had to add new codes availabe from the keyboard. Implementing the shift cursor control functionality required sacrificing the ability to use the keypad with Num Lock on. Also to use the shift cursor movements, you must do it with the numeric keypad - not the keys between the numeric key pad and the rest of the keyboard. These keys will still work for the unshifted and control cursor movements, but I could not get them to work with the shift key depressed.

I also added a program to put the minix OS image on the hardrive in /usr2/src/minix/sttools. It is called putminix. If you run 'make harddrive', make will use the Makefile to make sure the minix.img file is up to date before it writes it to the IDE drive. putminix, will report what it is going to do and asks for confirmation. When asked enter either y or n (case does not matter) followed by the Enter key.

There is also a program called key. Run it and you can see what each keystroke returns to the OS. DO NOT press the Delete or Del keys. If you do, you will have to exit and log back in to get screen scrolling to work. The program puts the keyboard in RAW and CBREAK mode. Entering the Delete or Del key will terminate the program before it gets a chance to set the sgtty structure for the console back to what it was originally.

The SD Card requires at least version 2.3 of HUMBUG dated 12/28/24. You can use either the WD or the MI command to boot from the SD Card. WD will use the bootloader on the hard drive and MI will use the built in HUMBUG boot loader. Using the WD command to use the SD Card resident boot loader is made possible by having a VERY small SK\*DOS partition on the drive that minix knows nothing about. It's just a few sectors that fool HUMBUG into thinking it is booting SK\*DOS. The program that is actually booted is the minix boot loader.

Once booted, the user name to login with is 'root' and the password is 'merlin'.

Future plans are to put the WD1002-WX1 driver back in and add support for the 37C65 floppy controller. This interface is built into the PT68K-4 and is an addin ISA card on the PT68K-2. 

To make turn around time while testing code go quicker, I am using a very small SD Card. It is a 256MB card (yes - MB not GB). Using a small card allows me to back up the image very quickly before commiting changes with putminix. It also allows me make a version of the image for the PT68K-2. I use the PT68K-4 for development, but test on both. The PT68K-4 is just so much faster. Also - using a class 10 SD card .vs. a class 4 card makes a big difference in performance.

The file FloppyMaintenance can be used to view the SD Card image. It is a Windows program, but it does run under Wine on linux. To get the latest version of FloppyMaintenance visit http://www.swtpcemu.com/swtpc/Downloads.htm.

I have added to umacs the reporting of the current line and column to the status line whenever the cursor position changes. The next step is to change the attribute of the marked text to bold. This will allow the user to be able to see what text is being marked.

As I think of more changes I made, I will update this README.md file.
