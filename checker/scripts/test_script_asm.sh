# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_script_asm.sh                                 :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/10 22:48:52 by skpn              #+#    #+#              #
#    Updated: 2020/04/17 19:34:55 by user42           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

usage_msg="sh script_asm binary_name [options] path/to/file[s].s\n"
usage_msg+="options:\n"
usage_msg+="\t-keep    : keep exec cor file\n"
usage_msg+="\t-show_err: show diff and exit script on error\n"
usage_msg+="\t-show_out: show what the exec prints to stdout\n"

output_dir=/tmp
parent_dir=$HOME/corewar_push_repo
ref_dir_hex=$parent_dir/checker/champ/hex_files
ref_dir_cor=$parent_dir/checker/champ/cor_files
exec_dir=$parent_dir/asm/

args=("$@")
exec=$1
show_err=0
show_out=0
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

if [ "$#" -lt 2 ]; then
	echo -e $usage_msg
	exit 1
fi

make -C $exec_dir &> $output_dir/check_make

if grep -q -e "Error" -e "error" $output_dir/check_make; then
	cat $output_dir/check_make
	exit
else
	rm -rf $output_dir/check_make
fi


######## PARSE ARGS #########

idx=1

while [ $idx -lt "$#" ]
do
##
	arg=${args[$idx]}
##
	if [ $arg == "-show_err" ]; then
		show_err=1
##
	elif [ $arg == "-show_out" ]; then
		show_out=1
##
	elif [ ! -f $arg ]; then
		echo "File '"$arg"'" not found
		exit 1
##
	elif [ ${arg: -2} != ".s" ]; then
		echo bad file extension: $arg
##
	elif [ ${#arg} -lt 3 ]; then
		echo file name too short: $(arg $s_file)
##
	else
		s_files_array+=($arg)
##
	fi
##
	idx=$(($idx + 1))
##
done


######## LAUNCH CHECKS #########

rm -f $output_dir/failed_tests > /dev/null

current_check=0
max_check=${#s_files_array[@]}
if [ $max_check -lt 1 ]; then
	echo no valid test files
	exit
fi
score=0
echo "failed tests:" > $output_dir/failed_tests
failed_nb=0

while [ $current_check -lt $max_check ]
do
	s_file=${s_files_array[$current_check]}
	ref_dir_s=${s_file%/*}
	current_check=$(($current_check + 1))
	shortname=$(basename $s_file)
	shortname=${shortname%.*}
	check_dir=$output_dir/$shortname
	echo -ne "\n[$current_check / $max_check]: $shortname - "

## CREATE DIR
	mkdir -p $check_dir
	rm -rf $check_dir/* &> /dev/null

## RUN EXEC
	./$exec $s_file &> $check_dir/exec
	if grep -q -e "SEGV" -e "leak" $check_dir/exec; then
		cat $output_dir/check_make
		exit
	fi

## GET HEXDUMPS
	cor_file="$shortname.cor"
	hexdump $ref_dir_cor/$cor_file > $ref_dir_hex/$shortname
	hexdump $ref_dir_s/$cor_file > $check_dir/hex
	if [ $keep == 1]; then
		mv $ref_dir_s/$cor_file $check_dir/cor
	else
		rm $ref_dir_s/$cor_file
	fi

## CHECK RESULTS
	diff $check_dir/hex $ref_dir_hex/$shortname > $check_dir/diff
	if [ -s $check_dir/diff ]; then
		echo -e $RED"ERROR"$NC
		echo " - " $s_file >> $output_dir/failed_tests
		failed_nb=$(($failed_nb + 1))
		if [ $show_err == 1 ]; then
			vim -O $check_dir/hex $ref_dir_hex/$shortname $check_dir/diff
			exit
		fi
	else
		echo -e $GREEN"OK"$NC
		score=$(($score + 1))
	fi
	if [ $show_out == 1 ]; then
		cat $check_dir/exec
	fi
	echo -e "\n"
##
done

echo final score: [ $score / $max_check ]
if [ $failed_nb -gt 0 ]; then
	echo -ne $failed_nb " "
	cat $output_dir/failed_tests
fi
