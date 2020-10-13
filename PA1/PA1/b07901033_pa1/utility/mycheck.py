import sys
import os


def check_file(infile_path,out_file_path):

    in_file = open(infile_path, "r")

    total_len = -1

    my_arr = []

    for x in in_file:
        if "points" in x:
            total_len = int(x.split()[1])
        elif "index" in x:
            continue
        else:
            my_arr.append(int(x.split()[1]))

    my_arr.sort()

    out_file = open(out_file_path, "r")

    for x in out_file:

        if "points" in x:
            if not int(x.split()[1]) == total_len:
                print("[dismatch] total count error")
        elif "index" in x:
            continue
        else:
            a =  int(x.split()[0])
            b =  int(x.split()[1])
            if not  my_arr[a] == b:
                print("[dismatch] wrong at index {}".format(a))
                return 0

    print("[match] Congratulations!!!")
    return 1


if os.path.isdir(sys.argv[1]):
    total = len(os.listdir(sys.argv[1]))
    match = 0
    not_exist = 0
    for x in os.listdir(sys.argv[1]):
        in_p = os.path.join(sys.argv[1], x)
        out_p = os.path.join(sys.argv[2], x ) + ".out"
        print("check {}".format(in_p))
        if os.path.exists(out_p):
            if check_file(in_p,out_p):
                match+=1
        else:
            print("{} does not exist".format(out_p))
            not_exist+=1
        print("="*20)

    print("[Summary] match {}/{} match(X not exist) {}/{}".format(match,total,match,total-not_exist))

else:
    check_file(sys.argv[0],sys.argv[1])