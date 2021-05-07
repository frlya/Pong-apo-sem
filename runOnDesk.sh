#!/bin/bash

scp -i ~/.ssh/mzapo-root-key /Users/frolka666/codes/apo_sem/*.c root@192.168.2.2:~/SEM_AS/apo_sem
scp -i ~/.ssh/mzapo-root-key /Users/frolka666/codes/apo_sem/*.h root@192.168.2.2:~/SEM_AS/apo_sem   

ssh -i ~/.ssh/mzapo-root-key root@192.168.2.2 <<END
cd ~/SEM_AS/apo_sem
make
./pong
END
echo "DONE"