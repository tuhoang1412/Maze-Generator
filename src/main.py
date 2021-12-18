from collections import namedtuple
from typing import NamedTuple
import sys
import os
from time import sleep
import random


def generate_maze(input_size: int) -> None:
    maze = [["X" for _ in range(input_size)] for _ in range(input_size)]
    global location
    location = namedtuple("location", ["x", "y"])
    printMaze(maze)
    start_location = location(0, 0)
    maze[0][0] = " "
    visited = []
    stack_moves = []
    os.system("cls")
    printMaze(maze)
    os.system("cls")
    stack_moves.append(start_location)
    while stack_moves:
        cur_location = stack_moves[-1]
        if load_nearby(cur_location, stack_moves, visited, maze):
            next_location = stack_moves[-1]
            maze[next_location[0]][next_location[1]] = " "
            maze[(cur_location[0] + next_location[0]) // 2][(cur_location[1] + next_location[1]) // 2] = " "
            sleep(0.6)
            os.system("clear")
            printMaze(maze)
        else:
            stack_moves.pop()
        visited.append(cur_location)


def load_nearby(cur_location: NamedTuple, stack_moves: list, visited: list, maze: list) -> bool:
    moves_list = []
    for t in ((2, 0), (-2, 0), (0, 2), (0, -2)):
        if (
            (cur_location[0] + t[0]) >= 0
            and (cur_location[0] + t[0]) < len(maze)
            and 0 <= (cur_location[1] + t[1])
            and (cur_location[1] + t[1]) < len(maze)
            and (cur_location[0] + t[0], cur_location[1] + t[1]) not in visited
        ):
            moves_list.append(location(cur_location[0] + t[0], cur_location[1] + t[1]))

    if not moves_list:
        return False
    elif len(moves_list) > 1:
        random.shuffle(moves_list)

    stack_moves.append(moves_list[0])
    return True


def printMaze(maze: list) -> None:
    for _ in range(len(maze) + 1):
        print("X", end=" ")

    print("X")
    for row in maze:
        print("X", end=" ")

        for element in row:
            print(element, end=" ")
        print("X")

    for _ in range(len(maze) + 2):
        print("X", end=" ")


if __name__ == "__main__":
    input = int(sys.argv[1]) if len(sys.argv) > 1 else 7
    generate_maze(input * 2 - 1)
