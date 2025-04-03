# minix-for-the-PT68K-2-4
This is the minix version 1.4b distribution I have been working on for the Peripheral Technology PT68K-2 and PT68K-4 compulters.

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

There is also a program called key. Run it and you can see what each keystroke returns to the OS. DO NOT press the Delete or Del keys. If you do, you will have to exit and log back in to get screen scrolling to work. The program puts the keyboard in RAW and CREAK mode.Entering the Delete or Del key will terminate the program before it gets a chance to set the sgtty structure for the console back to what it was originally.

The SD Card requires at least version 2.3 of HUMBUG dated 12/28/24. You can use either the WD or the MI command to boot from the SD Card. WD will use the bootloader on the hard drive and MI will use the built in HUMBUG boot loader. Using the WD command to use the SD Card resident boot loader is made possible by having a VERY small SK\*DOS partition on the drive that minix knows nothing about. It's just a few sectors that fool HUMBUG into thinking it is booting SK\*DOS. The program that is actually booted is the minix boot loader.

Once booted, the user name to login with is 'root' and the password is 'merlin'.

Future plans are to put the WD1002-WX1 driver back in and add support for the 37C65 floppy controller. This interface is built into the PT68K-4 and is an addin ISA card on the PT68K-2. 

To make turn around time while testing code go quicker, I am using a very small SD Card. It is a 256MB card (yes - MB ont GB). Using a small card allows me to back up the image very quickly before commiting changes with putminix. It also allows me make a version of the image for the PT68K-2. I use the PT68K-4 for development, but test on both. The PT68L-4 is just so much faster. Also - using a class 10 SD card .vs. a class 4 card makes a big difference in performance.

The file FloppyMaintenance can be used to view the SD Card image. It is a Windows program, but it does run under Wine on linux.

I have added to umacs the reporting of the current line and column to the status line whenever the cursor position changes. The next step is to change the attribute of the marked text to bold. This will allow the user to be able to see what text is being marked.

As I think of more changes I made, I will update this README.md file.
