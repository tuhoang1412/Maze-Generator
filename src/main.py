from collections import namedtuple
from typing import List, NamedTuple, Tuple
import sys
import os
import random
from time import sleep


def generateRand() -> None:
    starting_location = location(len(maze) - 1, 0)
    os.system("cls")
    printMaze(maze)
    moveNext(starting_location, input * 2 - 1)
    maze[-1][0] = " "
    os.system("cls")
    printMaze(maze)


def moveNext(cur_location: NamedTuple, size: int) -> bool:
    if (cur_location[0], cur_location[1]) in visited:
        return False
    visited.append((cur_location[0], cur_location[1]))
    moves_list = []
    for t in ((2, 0), (-2, 0), (0, 2), (0, -2)):
        if (
            (cur_location[0] + t[0]) in range(size)
            and (cur_location[1] + t[1]) in range(size)
            and not (cur_location[0] + t[0], cur_location[1] + t[1]) in visited
        ):
            moves_list.append(location(cur_location[0] + t[0], cur_location[1] + t[1]))

    if moves_list:
        random.shuffle(moves_list)
        for move in moves_list:
            if moveNext(move, size):
                maze[(cur_location[0] + move[0]) // 2][(cur_location[1] + move[1]) // 2] = " "
                maze[move[0]][move[1]] = " "
                sleep(0.3)
                os.system("cls")
                printMaze(maze)
    return True


def printMaze(maze: List) -> None:
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
    # sleep(2)
    # os.system("cls")
    # sleep(2)
    # print("Y")
    # sleep(2)


input = int(sys.argv[1]) if len(sys.argv) > 1 else 10
maze = [["X" for _ in range(input * 2 - 1)] for _ in range(input * 2 - 1)]
location = namedtuple("location", ["x", "y"])
visited = []
generateRand()
