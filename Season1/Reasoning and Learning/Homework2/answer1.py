import numpy as np
import re
import random

# Student Name:Yao XIAO, Student Number:2019180015|6641751 

# set gamma 
gamma = 0.8

# set transition matrix
t_matrix = []

# set actions which can be valid to move
actions = []

file_object = open('DB.pl', 'r')

# record chosen coordinate
chosen_coord = []

final_coord = None

start_coord = None

try:
    for line in file_object:
        if 's(' in line:
            col_and_row = re.findall(r'\d+', line)
            col = int(col_and_row[1])
            row = int(col_and_row[0])
            chosen_coord.append((row, col))
        elif 'goalState' in line:
            col_and_row = re.findall(r'\d+', line)
            col = int(col_and_row[1])
            row = int(col_and_row[0])
            final_coord = (row, col)
        elif 'startState' in line:
            col_and_row = re.findall(r'\d+', line)
            col = int(col_and_row[1])
            row = int(col_and_row[0])
finally:
    file_object.close()
print('\n')
print('It is chose coord which is valid:')
print(chosen_coord)

start_coord = (5, 2)
reward_matrix = np.zeros((len(chosen_coord), 4))
reward_matrix = reward_matrix - 1

# set up, down, left, right coord
up_coord = (final_coord[0], final_coord[1] + 1)
down_coord = (final_coord[0], final_coord[1] - 1)
left_coord = (final_coord[0] - 1, final_coord[1])
right_coord = (final_coord[0] + 1, final_coord[1])
if up_coord in chosen_coord:
    index = chosen_coord.index(up_coord)
    reward_matrix[index][1] = 10

if down_coord in chosen_coord:
    index = chosen_coord.index(down_coord)
    reward_matrix[index][0] = 10

if left_coord in chosen_coord:
    index = chosen_coord.index(left_coord)
    reward_matrix[index][3] = 10

if right_coord in chosen_coord:
    index = chosen_coord.index(right_coord)
    reward_matrix[index][2] = 10
print('\n')
print('Here is the reward matrix:')
print(reward_matrix)


f_matrix = np.zeros((len(chosen_coord), 4))
for point in chosen_coord:
    action_tmp = []
    tmp_trans = []
    # up step
    if (point[0], point[1] + 1) in chosen_coord:
        action_tmp.append(0)
        index = chosen_coord.index((point[0], point[1] + 1))
        tmp_trans.append(index)
    else:
        tmp_trans.append(-1)

    # down step
    if (point[0], point[1] - 1) in chosen_coord:
        action_tmp.append(1)
        index = chosen_coord.index((point[0], point[1] - 1))
        tmp_trans.append(index)
    else:
        tmp_trans.append(-1)

    # left step
    if (point[0] - 1, point[1]) in chosen_coord:
        action_tmp.append(2)
        index = chosen_coord.index((point[0] - 1, point[1]))
        tmp_trans.append(index)
    else:
        tmp_trans.append(-1)

    # right step
    if (point[0] + 1, point[1]) in chosen_coord:
        action_tmp.append(3)
        index = chosen_coord.index((point[0] + 1, point[1]))
        tmp_trans.append(index)
    else:
        tmp_trans.append(-1)
    actions.append(action_tmp)
    t_matrix.append(tmp_trans)
print('\n')
print('Here is the transition matrix:')
print(t_matrix)


for i in range(500):
    start_status = chosen_coord.index(start_coord)
    current_status = start_status
    while current_status != chosen_coord.index(final_coord):
        action = random.choice(actions[current_status])
        next_status = t_matrix[current_status][action]
        future_rewards = []
        for action_nxt in actions[next_status]:
            future_rewards.append(f_matrix[next_status][action_nxt])
        f_status = reward_matrix[current_status][action] + gamma * max(future_rewards)
        f_matrix[current_status][action] = f_status
        current_status = next_status
        if current_status == chosen_coord.index(final_coord):
            pass

print('\n')
print('Here is the final matrix:')
print(f_matrix)

# It is to present each action
start_status = chosen_coord.index(start_coord)
current_status = start_status
print('\n')
print('Here is each action:')
while current_status != chosen_coord.index(final_coord):
    print(current_status, chosen_coord[current_status])
    tmp = f_matrix[current_status].tolist()
    max_reward = min(tmp)
    action = tmp.index(min(tmp))
    for index, reward in enumerate(tmp):
        if reward > max_reward and reward != 0:
            max_reward = reward
            action = index

    next_status = t_matrix[current_status][action]
    current_status = next_status
    if current_status == chosen_coord.index(final_coord):
        print('\n' + 'Success Goal!')
