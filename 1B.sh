#!/bin/bash

while [ true ]
do
    echo "--------------MENU--------------"
    printf "1.Create\n2.View\n3.Insert\n4.Modify\n5.Delete\n6.Exit\n"
    echo "Enter the Choice:"
    read choice

    case $choice in
        1)
        echo "Enter Book Name:" 
        read file
        rm $file
        touch $file
        printf "RollNo\tName\tAddress\n" | cat >> $file
        printf "\nAddress Book Created\n\n"
        ;;

        2)
        printf "\n"
        cat $file
        printf "\n\n"
        ;;

        3)
        echo "Enter Name:"
        read name
        len=`cat $file | grep $name | wc -w`
        if [ $len -gt 0 ]
        then 
            echo "\nError: Record Already Exist!\n\n"
        else
            echo "Enter Roll No:"
            read rollno
            echo "Enter Address:"
            read add
            printf "$rollno\t$name\t$add\n" | cat >> $file
            printf "\nRecord Inserted\n\n"
        fi
        ;;

        4)
        echo "Enter Name:"
        read name
        len=`cat $file | grep $name | wc -w`
        if [ $len -gt 0 ]
        then
            echo "Enter Roll No:"
            read rollno
            echo "Enter Address:"
            read add
            new=`printf "$rollno\t$name\t$add\n"`
            old=`cat $file | grep $name`
            sed -i s/"$old"/"$new"/g $file
            echo "\nRecord Modified\n\n"
        else    
            printf "\nError: Record Doesn't Exist!\n\n"
        fi
        ;;

        5)
        printf "\nEnter the Name of Record to be Deleted:\n"
        read name
        temp="temp"
        grep -v $name $file | cat >> $temp 
        rm $file
        cat $temp | cat >> $file
        rm $temp
        printf "\n Record Deleted Successfully\n\n"
        ;;

        6)exit ;;

        7)echo "Wrong Choice" ;;
    
    esac
done