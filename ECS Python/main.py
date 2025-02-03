import esper
import pygame
import entity


# pygame setup
pygame.init()
screen = pygame.display.set_mode((1280, 720))
clock = pygame.time.Clock()
running = True
delta = 0


# Setup player
player = esper.create_entity()
player_position_component = entity.Position(pygame.Vector2(0.0, 0.0))
esper.add_component(player, entity.Velocity)
esper.add_component(player, player_position_component)
esper.add_component(player, entity.CircleRenderer(screen, player_position_component, 30.0))

esper.add_processor(player, entity.MovementProcessor(), 2)
esper.add_processor(player, entity.ControlledMovementProcessor(), 1)
esper.add_processor(player, entity.RendererProcessor())


while running:
    # poll for events
    # pygame.QUIT event means the user clicked X to close your window
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
    
    # process all systems
    esper.process()

    # fill the screen with a color to wipe away anything from last frame
    screen.fill("purple")

    # flip() the display to put your work on screen
    pygame.display.flip()

    # limits FPS to 60
    # dt is delta time in seconds since last frame, used for framerate-
    # independent physics.
    delta = clock.tick(155) / 1000

pygame.quit()