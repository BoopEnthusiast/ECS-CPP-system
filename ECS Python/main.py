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
esper.add_component(player, entity.Velocity(300.0))
esper.add_component(player, entity.Position(pygame.Vector2(0.0, 0.0)))
esper.add_component(player, entity.CircleRenderer(screen, 30.0))
esper.add_component(player, entity.JumpForce())
esper.add_component(player, entity.GravityForce())

esper.add_processor(entity.MovementProcessor())
esper.add_processor(entity.ControlledMovementProcessor())
esper.add_processor(entity.RendererProcessor())
esper.add_processor(entity.GravityProcessor())

esper.set_handler("jump", entity.JumpEvent.jump)


while running:
    # poll for events
    # pygame.QUIT event means the user clicked X to close your window
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
        elif event.type == pygame.KEYDOWN:
            if event.key == pygame.K_SPACE:
                esper.dispatch_event("jump")
    

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