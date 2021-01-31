""" After a line is read and processed, we do not need it anymore. So no datastructures except for a counter to keep track of no. of correct passwords.
    - Set "valid_password_counter" to 0
    - Split the line by spaces to fill 3 variables:
    -- (1) pos1-pos2 pair -- includes '-' sign
    -- (2) character to be searched
    -- (3) password
    -
    - Split the pos1-pos2 pair by '-' to fill 2 variables:
    -- (1) pos_1
    -- (2) pos_2
    - Then,
    -- if password[pos_1 -1] XOR password[pos_2-1] returns True, increment "valid_password_counter" by 1
    - At the end of loop, print "valid_password_counter"
"""
def execute():
    valid_password_counter = 0

    for line in lines:    
        ps1_pos2_pair, character, password = line.split()
        pos_1, pos_2 = map(int, ps1_pos2_pair.split('-'))
        character = character[0]
    
        """print(min_count, max_count, character, password)"""

        if (password[pos_1 - 1] == character)^(password[pos_2 - 1] == character):
            valid_password_counter += 1
    
    print(valid_password_counter)

lines = open('day2.input', 'r')

execute()

