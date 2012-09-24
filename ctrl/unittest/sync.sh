#rsync -r -t -v --progress --exclude ".*" --exclude "build__" --exclude "ctrl" wliu@192.168.0.$1:/root/CMVision/trunk/ctrl/ .
rsync -r -t -v --progress root@192.168.0.$1:/root/CMVision/trunk/ctrl/*.log .
