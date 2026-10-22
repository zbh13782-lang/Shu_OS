#!/bin/bash
set -e
cd "$(dirname "$0")"
echo "实验三：进程管理及进程通信 | 翟博豪 24122233"
echo "账户：$(id -un) | 主机：$(hostname) | 目录：$PWD"
case "$1" in
    1) ./01_identity_exec ;;
    2) ./02_fork_wait ;;
    3) printf 'tree\n' | ./03_process_tree
       printf 'chain\n' | ./03_process_tree
       printf 'siblings\n' | ./03_process_tree ;;
    4) echo "=== 第1次运行 ==="
       ./04_multi_exec
       echo "=== 第2次运行 ==="
       ./04_multi_exec ;;
    5) ./05_memory_copy ;;
    6) ./06_pipe 0 500 before
       ./06_pipe 500 0 before
       ./06_pipe 0 500 after ;;
    7) printf 'reap\n' | ./07_lifecycle
       printf 'orphan\n' | ./07_lifecycle
       sleep 3 ;;
    8) ./run_08.sh ;;
    9) ./09_signal ;;
    10) ./10_producer_consumer ;;
    *) echo "用法：./run_step.sh 题号（1 到 10）"; exit 1 ;;
esac
