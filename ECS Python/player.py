import pygame
from typing import Final

class Player():
    SPEED: Final = 300.0
    position: pygame.Vector2 = pygame.Vector2()


    def move(delta: float) -> None:
        keys = pygame.key.get_pressed()
        velocity = pygame.Vector2()
        
        if keys[pygame.K_w]:
            velocity.y -= 1
        if keys[pygame.K_s]:
            velocity.y += 1
        if keys[pygame.K_a]:
            velocity.x -= 1
        if keys[pygame.K_d]:
            velocity.x += 1
        
        if velocity.length_squared() > 0:
            velocity = velocity.normalize()

        Player.position += velocity.xy * delta * Player.SPEED
    
    
    def draw(delta: float) -> None:
        Player.move(delta)