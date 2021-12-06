#!/bin/bash

make re n=std > /dev/null || exit 1
./ft_containers > std.out 2> stderr.out || exit 1

make re > /dev/null || exit 1
./ft_containers > ft.out 2> fterr.out || exit 1

diff -a std.out ft.out > diff.out || less diff.out
