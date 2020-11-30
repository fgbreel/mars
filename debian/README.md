Building the dkms package:

```
user@plug:/home/user/$ git clone https://github.com/fgbreel/mars.git && cd mars

user@plug:/home/user/mars$ git checkout debian/sid

user@plug:/home/user/mars$ gbp buildpackage --git-pristine-tar --git-pristine-tar-commit --git-upstream-tag='mars%(version)s' --git-debian-branch=debian/sid -us -uc
gbp:info: Creating /home/user/mars_0.1astable114.orig.tar.gz
gbp:info: Performing the build
 dpkg-buildpackage -us -uc -ui -i -I
dpkg-buildpackage: info: source package mars
dpkg-buildpackage: info: source version 0.1astable114-1
dpkg-buildpackage: info: source distribution unstable
dpkg-buildpackage: info: source changed by Gabriel Francisco <frc.gabriel@gmail.com>
 dpkg-source -i -I --before-build .
dpkg-buildpackage: info: host architecture amd64
 fakeroot debian/rules clean
dh clean --with dkms
   debian/rules override_dh_auto_clean
make[1]: Entering directory '/home/user/mars'
make[1]: Leaving directory '/home/user/mars'
   dh_clean
 dpkg-source -i -I -b .
dpkg-source: info: using source format '3.0 (quilt)'
dpkg-source: info: building mars using existing ./mars_0.1astable114.orig.tar.gz
dpkg-source: info: building mars in mars_0.1astable114-1.debian.tar.xz
dpkg-source: info: building mars in mars_0.1astable114-1.dsc
 debian/rules build
dh build --with dkms
   dh_update_autotools_config
   dh_autoreconf
   create-stamp debian/debhelper-build-stamp
 fakeroot debian/rules binary
dh binary --with dkms
   dh_testroot
   dh_prep
   debian/rules override_dh_install
make[1]: Entering directory '/home/user/mars'
cp debian/mars-Makefile kernel/Makefile
cp debian/mars-Kbuild kernel/Kbuild
dh_install scripts/gen_config.pl usr/src/mars-0.1astable114/
dh_install kernel/* usr/src/mars-0.1astable114/
make[1]: Leaving directory '/home/user/mars'
   dh_installdocs
   dh_installchangelogs
   dh_installman
   dh_installcron
   debian/rules override_dh_dkms
make[1]: Entering directory '/home/user/mars'
dh_dkms -V 0.1astable114
make[1]: Leaving directory '/home/user/mars'
   dh_perl
   dh_link
   dh_strip_nondeterminism
   dh_compress
   dh_fixperms
   dh_missing
   dh_strip
   dh_makeshlibs
   dh_shlibdeps
   dh_installdeb
   dh_gencontrol
   dh_md5sums
   dh_builddeb
dpkg-deb: building package 'mars-dkms' in '../mars-dkms_0.1astable114-1_amd64.deb'.
dpkg-deb: building package 'mars-tools' in '../mars-tools_0.1astable114-1_amd64.deb'.
 dpkg-genbuildinfo
 dpkg-genchanges  >../mars_0.1astable114-1_amd64.changes
dpkg-genchanges: info: including full source code in upload
 dpkg-source -i -I --after-build .
dpkg-buildpackage: info: full upload (original source is included)
```

Installing on target computer:

```
root@plug:/home/user# apt install ./mars-dkms_0.1astable114-1_amd64.deb
Reading package lists... Done
Building dependency tree
Reading state information... Done
Note, selecting 'mars-dkms' instead of './mars-dkms_0.1astable114-1_amd64.deb'
The following NEW packages will be installed:
  mars-dkms
0 upgraded, 1 newly installed, 0 to remove and 100 not upgraded.
Need to get 0 B/223 kB of archives.
After this operation, 1144 kB of additional disk space will be used.
Get:1 /home/user/mars-dkms_0.1astable114-1_amd64.deb mars-dkms amd64 0.1astable114-1 [223 kB]
Selecting previously unselected package mars-dkms.
(Reading database ... 222033 files and directories currently installed.)
Preparing to unpack .../mars-dkms_0.1astable114-1_amd64.deb ...
Unpacking mars-dkms (0.1astable114-1) ...
Setting up mars-dkms (0.1astable114-1) ...
Loading new mars-0.1astable114 DKMS files...
Building for 4.9.0-13-amd64
Building initial module for 4.9.0-13-amd64
Done.

mars.ko:
Running module version sanity check.
 - Original module
   - No original module exists within this kernel
 - Installation
   - Installing to /lib/modules/4.9.0-13-amd64/updates/dkms/

depmod...

DKMS: install completed.

root@plug:/home/user# stat /lib/modules/4.9.0-13-amd64/updates/dkms/mars.ko
  File: /lib/modules/4.9.0-13-amd64/updates/dkms/mars.ko
  Size: 861440    	Blocks: 1688       IO Block: 4096   regular file
Device: fe01h/65025d	Inode: 525826      Links: 1
Access: (0644/-rw-r--r--)  Uid: (    0/    root)   Gid: (    0/    root)
Access: 2020-11-19 18:20:55.082662798 +0100
Modify: 2020-11-19 18:20:54.862664958 +0100
Change: 2020-11-19 18:20:54.862664958 +0100
 Birth: -
```

Return from `dmesg` from target computer:

```
root@plug:/home/user# fallocate -l 10G foo
root@plug:/home/user# losetup -f foo
root@plug:/home/user# vgcreate mars /dev/loop0
root@plug:/home/user# lvcreate -n mars -L 9G mars
root@plug:/home/user# mkfs -t ext4 /dev/mapper/mars-mars
root@plug:/home/user# mount /dev/mapper/mars-mars /mars/
root@plug:/home/user# modprobe mars

root@plug:/home/user# dmesg  | tail
[44413.535164] Cluster UUID is missing. Mount /mars/, and/or say {create,join}-cluster afterwwards.
[44413.535172] loading MARS, BUILDTAG=no-buildtag-available BUILDHOST=user@plug BUILDDATE=2020-11-20 03:31:33
[44413.590445] crc32c     digest duration =     56001256 ns
[44413.633954] crc32      digest duration =     44000989 ns
[44413.929130] sha1       digest duration =    296006661 ns
[44414.185517] md5old     digest duration =    256005761 ns
[44414.449394] md5        digest duration =    264005939 ns
[44414.484375] lzo      compress duration =     36000810 ns
[44414.526621] lz4      compress duration =     40000900 ns
[44415.499954] zlib     compress duration =    976021964 ns
```

Create and join a cluster:

```
root@istore-test-bap7:~# marsadm join-cluster istore-test-bs7
DYING: cannot create symlink '/mars/actual-istore-test-bap7/marsadm-version' -> '2.9'
FAILURE cmd='join-cluster' res='istore-test-bs7'

root@istore-test-bap7:~# marsadm join-cluster --ip=192.168.33.20 istore-test-bs7   
Using IP '192.168.33.20' from command line for 'istore-test-bap7'.
DYING: Cannot determine foreign IP for peer 'istore-test-bs7'
FAILURE cmd='join-cluster' res='istore-test-bs7'


root@istore-test-bap7:~# marsadm join-cluster --ip=192.168.33.20 istore-test-bs7
Using IP '192.168.33.20' from command line for 'istore-test-bap7'.
DNS query for 'istore-test-bs7' found IPv4 address '192.168.33.10'
MARS kernel module is loaded, trying the new join-cluster method.
Update local 'istore-test-bap7' information
Ping istore-test-bap7 trigger=8
Wait for answers from istore-test-bap7
WARNING: Need restart for getting more 'time' links
Ping istore-test-bap7 trigger=8
Wait for answers from istore-test-bap7
1/1 peer(s) seem to be alive
Checking uuid
... update from istore-test-bs7 round 1
Ping istore-test-bs7 trigger=8
Wait for answers from istore-test-bs7
1/1 peer(s) seem to be alive
Successfully joined cluster, uuid='istore-test-bs7 Mon Nov 30 03:07:42 GMT 2020'
```


```
WARNING: resource qualifier 'all' does not match any resource or guest names
root@istore-test-bap7:/mars# marsadm join-resource bar /dev/loop1
OK, resource directory '/mars/resource-bar' exists.
Ping istore-test-bap7 trigger=2
Wait for answers from istore-test-bap7
1/1 peer(s) seem to be alive
Ping * trigger=8
Wait for answers from istore-test-bs7
1/1 peer(s) seem to be alive
joining to existing resource 'bar'
block device '/dev/loop1': determined size = 1073741824 bytes
OK, resource directory '/mars/resource-bar' exists.
Ping * trigger=3
Wait for answers from istore-test-bs7
1/1 peer(s) seem to be alive
found replay link '/mars/resource-bar/replay-istore-test-bs7' -> 'log-000000002-istore-test-bs7,0,0'
found replay link '/mars/resource-bar/replay-istore-test-bs7' -> 'log-000000002-istore-test-bs7,0,0'
checking 'version-000000001-istore-test-bs7'
  corresponding logfile is 'log-000000001-istore-test-bs7'
  ok 'version-000000001-istore-test-bs7'
checking 'version-000000002-istore-test-bs7'
  corresponding logfile is 'log-000000002-istore-test-bs7'
  ok 'version-000000002-istore-test-bs7'
info: logfile 'log-000000001-istore-test-bs7' is referenced (1), but not present.
info: logfile 'log-000000002-istore-test-bs7' is referenced (1), but not present.
  Unreferenced logfiles are not necessarily bad.
  They can regularly appear after 'leave-resource',
  or 'invalidate', or after emergency mode,
  or after similar operations.
waiting for deletions to apply locally....
using existing device '/dev/loop1'
resource 'bar' will appear as local device '/dev/mars/bar'
creating new replaylink '/mars/resource-bar/replay-istore-test-bap7' -> 'log-000000002-istore-test-bs7,0,0'
Creating new versionlink '/mars/resource-bar/version-000000002-istore-test-bap7' -> 'e01d67655265eb5853501277ecd89d13,log-000000002-istore-test-bs7,0:7208f7b776ce4801c1a0da69e8bc635d,log-000000001-istore-test-bs7,69872880'
Creating new versionlink '/mars/resource-bar/version-000000001-istore-test-bap7' -> '7208f7b776ce4801c1a0da69e8bc635d,log-000000001-istore-test-bs7,69872880:'
Ping istore-test-bs7 trigger=2
Wait for answers from istore-test-bs7
1/1 peer(s) seem to be alive
Ping istore-test-bs7 trigger=2
Wait for answers from istore-test-bs7
1/1 peer(s) seem to be alive
Connection to 127.0.0.1 closed by remote host.
Connection to 127.0.0.1 closed.
```


Leaving resource:

```
root@istore-test-bap7:~# marsadm leave-resource all
-------- PHASE 1 -------- check preconditions:
--------- resource bar 1024.000 MiB [2/2]
OK at istore-test-bap7: '/mars/resource-bar/actual-istore-test-bap7/is-attached' has acceptable value '0'
-------- PHASE 2 -------- switch state:
--------- resource bar 1024.000 MiB [2/2]
-------- PHASE 3 -------- purge logfiles:
--------- resource bar 1024.000 MiB [2/2]
waiting for deletions to apply locally....
found replay link '/mars/resource-bar/replay-istore-test-bs7' -> 'log-000000002-istore-test-bs7,279483160,0'
found replay link '/mars/resource-bar/replay-istore-test-bs7' -> 'log-000000002-istore-test-bs7,279483160,0'
checking 'version-000000001-istore-test-bs7'
  corresponding logfile is 'log-000000001-istore-test-bs7'
  ok 'version-000000001-istore-test-bs7'
checking 'version-000000002-istore-test-bs7'
  corresponding logfile is 'log-000000002-istore-test-bs7'
  ok 'version-000000002-istore-test-bs7'
info: logfile 'log-000000001-istore-test-bs7' is referenced (1), but not present.
info: logfile 'log-000000002-istore-test-bs7' is referenced (1), but not present.
  Unreferenced logfiles are not necessarily bad.
  They can regularly appear after 'leave-resource',
  or 'invalidate', or after emergency mode,
  or after similar operations.
-------- PHASE 4 -------- wait for deletions:
WARNING: resource qualifier 'all' does not match any resource or guest names

root@istore-test-bap7:~# marsadm leave-cluster
Ping * trigger=3
Wait for answers from istore-test-bs7
1/1 peer(s) seem to be alive
Ping * trigger=3
Wait for answers from istore-test-bs7
1/1 peer(s) seem to be alive
Ping * trigger=3
Wait for answers from istore-test-bs7
1/1 peer(s) seem to be alive
```



PANIC
```
root@istore-test-bap7:~# marsadm leave-resource bar
-------- PHASE 1 -------- check preconditions:
OK at istore-test-bap7: '/mars/resource-bar/actual-istore-test-bap7/is-attached' has acceptable value '0'
-------- PHASE 2 -------- switch state:
-------- PHASE 3 -------- purge logfiles:
waiting for deletions to apply locally....
found replay link '/mars/resource-bar/replay-istore-test-bs7' -> 'log-000000003-istore-test-bs7,0,0'
found replay link '/mars/resource-bar/replay-istore-test-bs7' -> 'log-000000003-istore-test-bs7,0,0'
checking 'version-000000002-istore-test-bs7'
  corresponding logfile is 'log-000000002-istore-test-bs7'
  ok 'version-000000002-istore-test-bs7'
checking 'version-000000003-istore-test-bs7'
  corresponding logfile is 'log-000000003-istore-test-bs7'
  ok 'version-000000003-istore-test-bs7'
info: logfile 'log-000000002-istore-test-bs7' is referenced (1), but not present.
info: logfile 'log-000000003-istore-test-bs7' is referenced (1), but not present.
  Unreferenced logfiles are not necessarily bad.
  They can regularly appear after 'leave-resource',
  or 'invalidate', or after emergency mode,
  or after similar operations.
-------- PHASE 4 -------- wait for deletions:
waiting for deletions to apply locally....
systemd unit 'mars-trigger.path' is not existing or not enabled.
root@istore-test-bap7:~# marsadm join-resource bar /de^C
root@istore-test-bap7:~# losetup 
NAME       SIZELIMIT OFFSET AUTOCLEAR RO BACK-FILE         DIO
/dev/loop0         0      0         0  0 /home/vagrant/foo   0
root@istore-test-bap7:~# losetup -f bar 
root@istore-test-bap7:~# losetup 
NAME       SIZELIMIT OFFSET AUTOCLEAR RO BACK-FILE         DIO
/dev/loop1         0      0         0  0 /root/bar           0
/dev/loop0         0      0         0  0 /home/vagrant/foo   0
root@istore-test-bap7:~# marsadm join-resource bar /dev/loop1
OK, resource directory '/mars/resource-bar' exists.
Ping istore-test-bap7 trigger=2
Wait for answers from istore-test-bap7
1/1 peer(s) seem to be alive
Ping * trigger=8
Wait for answers from istore-test-bs7
1/1 peer(s) seem to be alive
joining to existing resource 'bar'
block device '/dev/loop1': determined size = 1073741824 bytes
OK, resource directory '/mars/resource-bar' exists.
Ping * trigger=3
Wait for answers from istore-test-bs7
1/1 peer(s) seem to be alive
found replay link '/mars/resource-bar/replay-istore-test-bs7' -> 'log-000000003-istore-test-bs7,0,0'
found replay link '/mars/resource-bar/replay-istore-test-bs7' -> 'log-000000003-istore-test-bs7,0,0'
checking 'version-000000002-istore-test-bs7'
  corresponding logfile is 'log-000000002-istore-test-bs7'
  ok 'version-000000002-istore-test-bs7'
checking 'version-000000003-istore-test-bs7'
  corresponding logfile is 'log-000000003-istore-test-bs7'
  ok 'version-000000003-istore-test-bs7'
info: logfile 'log-000000002-istore-test-bs7' is referenced (1), but not present.
info: logfile 'log-000000003-istore-test-bs7' is referenced (1), but not present.
  Unreferenced logfiles are not necessarily bad.
  They can regularly appear after 'leave-resource',
  or 'invalidate', or after emergency mode,
  or after similar operations.
waiting for deletions to apply locally....
using existing device '/dev/loop1'
resource 'bar' will appear as local device '/dev/mars/bar'
creating new replaylink '/mars/resource-bar/replay-istore-test-bap7' -> 'log-000000003-istore-test-bs7,0,0'
Creating new versionlink '/mars/resource-bar/version-000000003-istore-test-bap7' -> 'a64424bd50695f2557c1b83bbd317cb5,log-000000003-istore-test-bs7,0:8728a48cf769fd147be6683e3b8d6d59,log-000000002-istore-test-bs7,279483160'
Creating new versionlink '/mars/resource-bar/version-000000002-istore-test-bap7' -> '8728a48cf769fd147be6683e3b8d6d59,log-000000002-istore-test-bs7,279483160:7208f7b776ce4801c1a0da69e8bc635d,log-000000001-istore-test-bs7,69872880'
Ping istore-test-bs7 trigger=2
Wait for answers from istore-test-bs7
1/1 peer(s) seem to be alive
Ping istore-test-bs7 trigger=2
Wait for answers from istore-test-bs7
Connection to 127.0.0.1 closed by remote host.
Connection to 127.0.0.1 closed.
```
