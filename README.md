# ABMountWatcher
ABMountWatcher is a QT Object Class which is designed to run in a LINUX environment. It monitors a single mountpoint directory for changes; in this sense, if the mountpoint contains less than three files then ABMountWatcher assumes that there is nothing mounted, otherwise ABMountWatcher assumes there is a filesystem mounted in the directory specified.

ABMountWatcher accepts the following parameters on creation; QObject *parent*, QString *mountPoint*, bool *enabled*, int *pollPeriod*

If *mountPoint* is not specified on creation, then ABMountWatcher is disabled; if *mountPoint* does not reference a valid directory ABMountWatcher will report that no disk is mounted.

*pollPeriod* should be specified in milliSeconds; it defaults to 500ms if not otherwise set. *pollPeriod* can be changed by a call to *setPollPeriod(int)*.

ABMountWatcher is enabled by default; this can be changed on creation, or by a call to *setEnabled(bool)*;

The mountState(bool) signal is emitted when the number of files in the monitored directory changes to less than three; or changes to be more than two. The boolean state is *true* when the number of files in the monitored directory is more than two.

# The Reason for ABMountWatcher
QT provides a [QFileSystemWatcher](https://doc.qt.io/qt-5/qfilesystemwatcher.html) class, which, on first glance would seem to provide the same functionality as ABMountWatcher. However, in a Linux system [QFileSystemWatcher](https://doc.qt.io/qt-5/qfilesystemwatcher.html) relies on [inotify](http://manpages.ubuntu.com/manpages/bionic/man7/inotify.7.html) which is not responsive to filesystems being mounted on top of a monitored directory; cf:

    If  a filesystem is mounted on top of a monitored directory, no event is generated, and no
    events are generated for objects immediately under the new mount point.  If the filesystem
    is subsequently unmounted, events will subsequently be generated for the directory and the
    objects it contains.
