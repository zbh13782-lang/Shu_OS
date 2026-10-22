#!/bin/bash
cd "$(dirname "$0")" || exit 1
./08_server &
server_pid=$!
sleep 1
# 服务端创建失败时立即停止，避免误用已有队列。
kill -0 "$server_pid" 2>/dev/null || exit 1
for i in 1 2 3; do
    echo "--- client $i ---"
    ./08_client || exit 1
done
wait "$server_pid" || exit 1
# 三个客户都已读完回复，再清理本次实验的固定 key。
ipcrm -Q 0x24122233 || exit 1
echo QUEUE_REMOVED
