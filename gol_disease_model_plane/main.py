from board import Board
import numpy as np

def main():
    #assume the user types in a number
    user_rows = int(input('how many rows? '))
    user_columns = int(input('how many columns? '))

    print("<<Generation 1>>\n")
    # create a board:
    game_of_life_board = Board(user_rows,user_columns)

    #run the first iteration of the board:
    game_of_life_board.draw_board()
    #game_of_life_board.update_board()

    user_action = ''
    count = 1

    while user_action != 'q':
        #old_gen = np.array(game_of_life_board)
        #new_gen = game_of_life_board.update_board()
        game_of_life_board.update_board()
        #c = np.equal(game_of_life_board, game_of_life_board.update_board())
        #print("This is C:", c)

        if np.equal(game_of_life_board, game_of_life_board.update_board()) == False:
            user_action = input('Press enter to add generation or q to quit:')
            if user_action == '':
                count += 1
                print("<<Generation", count, ">>\n")
                #new_gen = np.array(game_of_life_board.update_board())
                #new_gen.draw_board()
                #game_of_life_board.update_board()
                game_of_life_board.draw_board()
        else:
            #print(count)
            print("It took", count, "generations to stabilize.")
            user_action = 'q'

main()