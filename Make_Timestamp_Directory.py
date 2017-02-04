import os
import json

def replace_spaces_in_quotes(old_string):
    inQuotes = False;

    new_string=""

    for c in old_string:
        if c=="\"":
            inQuotes = not inQuotes;
        if c==" ":
            if inQuotes==True:
                c = c.replace(" ","_")
        new_string += c
    return new_string

# def rid_quotes(old_string):
#     for c in old_string:
#         if c=="\"":
#             c=c.replace

# example = "Mariah said \"Hi my name is Mariah\" whats your name"

# print (replace_spaces_in_quotes(example))

for filename in os.listdir("/Users/akinbi/CODINGS/Ghost_Hack_17/AR_DataAnalytics/txtfiles"):
    if filename.endswith(".txt"):
        print (filename)
        the_file = open("/Users/akinbi/CODINGS/Ghost_Hack_17/AR_DataAnalytics/txtfiles/"+filename, "r")

        stamp_dictionary = {}

        with open("/Users/akinbi/CODINGS/Ghost_Hack_17/json_file","w") as f:
            content = the_file.readline()
            if content=="":
                continue
            # replace_spaces_in_quotes(content)
            content = replace_spaces_in_quotes(content)
            print (content)

            split_strings = content.split(' ')
            print (split_strings)
            name = split_strings[3]
            print (name)
            y2k = split_strings[9]
            print (y2k)


            stamp_dictionary[name] = y2k
            s = json.dumps(stamp_dictionary)
            print s

            f.write(s + '\n')
        


# stamp_file = open("/Users/akinbi/CODINGS/Ghost_Hack_17/AR_DataAnalytics/txtfiles/app_1.txt","r")
# content = stamp_file.readline() THIS WORKS
#
# print (content)
#
# split_string = content.split(' ')
#
# # print (split_string)
#
# name = str(split_string[3])
# print (name)
# y2k = split_string[14]
# print (y2k)
#
# stamp_dictionary = {}
#
# stamp_dictionary[name] = y2k
#
# print (stamp_dictionary)
#
# import json
# s = json.dumps(stamp_dictionary)


# with open("/Users/akinbi/CODINGS/Ghost_Hack_17/json_file","w") as f:
#     f.write(s)    THIS WORKS

# def remove_quotation_marks(x):
#     for string in x:
#         if string[0]=='\"':
