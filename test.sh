#!/bin/bash

make re n=std > /dev/null
./ft_containers > std.out 2> stderr.out

make re n=ft > /dev/null
./ft_containers > ft.out 2> fterr.out

diff std.out ft.out > diff.out
less diff.out
