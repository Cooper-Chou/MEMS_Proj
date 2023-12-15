#!/bin/bash

function check_ip(){
        IP=$1
	echo $IP
        VALID_CHECK=$(echo $IP|awk -F. '$1<=255 && $2<=255 && $3<=255 && $4<=255 {print "yes"}')
        if echo $IP|grep -E "^[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}$">/dev/null; then
                if [[ $VALID_CHECK == "yes" ]]; then
			return 0
                else
			return 1
                fi
        else
		return 2
        fi
}

echo "   ↖(▔▽▔)↗ ↖(▔▽▔)↗ Let's start our journey! ↖(▔▽▔)↗ ↖(▔▽▔)↗ "
echo "-----------------------------MENU-----------------------------"
echo -e "a. List all files in the present working directory\nb. Display today's date and time\nc. Display whether a file is a \"simple\" file or a \"directory\" \nd. Create a backup for a file \ne. Start an ftp session\nf. Start your LED control program\nm. Display menu again\nx. Exit"
echo "--------------------------------------------------------------"
declare -i end_flag=0
while [ $end_flag != "1" ]
do
	read -p "Please enter your operation (￣Д ￣)┍: " input;
	case $input in
		a)
			ls -l	
			;;
		b)
			date
			;;
		c)
			read -p "(Press ENTER to return to MENU) Please enter the object of your interest乀(ˉεˉ乀): " filename
			while [ ! -e $filename ]
			do
				read -p "You're NOT giving a valid name! Please RE-ENTER!(╬▔︹▔)凸: " filename
			done

			if [ -z $filename ]
			then
				continue
			fi

			if [ -d $filename ]
			then
				echo "$filename is a DIRECTORY!ヽ(ˋ▽ˊ)ノ"
			elif [ -f $filename ]
			then
				echo "$filename is a SIMPLE FILE!ヽ(ˋ▽ˊ)ノ"
			fi
			;;
		d)
			read -p "(Press ENTER to return to MENU) Please enter the file/directory that YOU WANT TO BACKUP乀(ˉεˉ乀): " filename
			while [ ! -e $filename ]
			do
				read -p "You're NOT giving a valid name! Please RE-ENTER!(╬▔︹▔)凸: " filename
			done

			if [ -z $filename ]
			then
				continue
			fi

			read -p "Please NAME THE BACKUP file/directory (just press ENTER for DEFAULT name)乀(ˉεˉ乀): " newname
			if [ -d $filename ]
			then
				if [ -z $newname ]
				then
					cp -i -r -p $filename "${filename}_backup"
				else
				 	cp -i -r -p $filename $newname
				fi
			elif [ -f $filename ]
			then
				if [ -z $newname ]
				then
					cp -i -p $filename "${filename%.*}_backup.${filename##*.}"
				else
				 	cp -i -p $filename $newname
				fi
			fi
			echo "DONE! Go and check it!ヽ(ˋ▽ˊ)ノ"
			;;
		e)
			read -p "(Press ENTER to return to MENU) Please enter the IP-ADDRESS (IPv4 ONLY!!!) of the FTP SEVER you want to connect乀(ˉεˉ乀): " address

			if [ -z $address ]
			then
				continue
			fi
			
			check_ip $address
			declare -i ipstate=$?			
			while [ $ipstate != "0" ]
			do
				read -p "You're NOT giving a valid ip-address! Please RE-ENTER!(╬▔︹▔)凸: " address
				check_ip $address
				ipstate=$?
			done
			
			ftp $address
			;;
		f)
			/home/cooper/MicroComProj/Proj_2/button_blink
			;;
		m)
			echo "-----------------------------MENU-----------------------------"
			echo -e "a. List all files in the present working directory\nb. Display today's date and time\nc. Display whether a file is a \"simple\" file or a \"directory\" \nd. Create a backup for a file \ne. Start an ftp session\nf. Start your LED control program\nm. Display menu again\nx. Exit"
			echo "--------------------------------------------------------------"
			;;
		x)
			end_flag="1"
			;;
		*)
			echo "You're entering a wrong argument! Please make it correct! (*▔＾▔*)"
			;;
	esac
done
echo "Thank you and see you next time! Have a nice day! (～￣▽￣)～"
