import esper
import pygame
import entity
import singleton


# pygame setup
pygame.init()
screen = pygame.display.set_mode((1280, 720))
clock = pygame.time.Clock()
running = True


# Setup player
player = esper.create_entity()
esper.add_component(player, entity.Velocity(100.0))
esper.add_component(player, entity.Position(pygame.Vector2(0.0, 0.0)))
esper.add_component(player, entity.CircleRenderer(screen, 30.0))

esper.add_processor(entity.MovementProcessor())
esper.add_processor(entity.ControlledMovementProcessor())
esper.add_processor(entity.RendererProcessor())


while running:
    # poll for events
    # pygame.QUIT event means the user clicked X to close your window
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
    

    # fill the screen with a color to wipe away anything from last frame
    screen.fill("purple")

    # process all systems
    esper.process()

    # flip() the display to put your work on screen
    pygame.display.flip()

    # limits FPS to 60
    # dt is delta time in seconds since last frame, used for framerate-
    # independent physics.
    singleton.delta = clock.tick(155) / 1000

pygame.quit()