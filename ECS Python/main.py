import esper
import pygame
from player import Player


# pygame setup
pygame.init()
screen = pygame.display.set_mode((1280, 720))
clock = pygame.time.Clock()
running = True
delta = 0

player: Player = Player

while running:
    # poll for events
    # pygame.QUIT event means the user clicked X to close your window
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    # fill the screen with a color to wipe away anything from last frame
    screen.fill("purple")

    pygame.draw.circle(screen, "red", player.position, 40)

    player.draw(delta)

    # flip() the display to put your work on screen
    pygame.display.flip()

    # limits FPS to 60
    # dt is delta time in seconds since last frame, used for framerate-
    # independent physics.
    delta = clock.tick(155) / 1000

pygame.quit()
# def main():
#     pygame.init()
#     screen = pygame.display.set_mode((1280, 720))
#     clock = pygame.time.Clock()
#     main_loop()
#     pygame.quit()
#     quit()


# def main_loop():
#     while True:
#         # Check for quitting
#         for event in pygame.event.get():
#             if event.type == pygame.QUIT:
#                 return

#         # Clear frame
#         screen.fill("purple")

#         pygame.display.flip()

#         clock.tick(155)

    

        


# if __name__ == "__main__":
#     main()