#!/bin/bash

scp -i ~/.ssh/mzapo-root-key /path/to/codes/directory/on/local/machine/*.c root@192.168.x.x:~/path/to/remote/folder

scp -i ~/.ssh/mzapo-root-key /path/to/codes/directory/on/local/machine/*.h root@192.168.x.x:~/path/to/remote/folder   

ssh -i ~/.ssh/mzapo-root-key root@192.168.x.x <<END
cd ~/path/to/remote/directory
make
./yourbinary
END
echo "DONE"