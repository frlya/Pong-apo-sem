#!/bin/bash

scp -i ~/.ssh/mzapo-root-key /Users/frolka666/codes/apo_sem/*.c root@192.168.2.2:~/SEM_AS/apo_sem
scp -i ~/.ssh/mzapo-root-key /Users/frolka666/codes/apo_sem/*.h root@192.168.2.2:~/SEM_AS/apo_sem   