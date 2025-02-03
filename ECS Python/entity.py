import pygame
import esper
from dataclasses import dataclass as component

@component
class Position:
    positionL: pygame.Vector2 = pygame.Vector2(0.0, 0.0)
    # the dataclass (renamed to component) decorator automatically generates an __init__ function

@component
class Velocity:
    x: float = 0.0
    y: float = 0.0

@component
class RectCollider:
    position: Position
    width: int
    height: int

    @property
    # Axis Aligned Bounding Box
    def aabb(self) -> tuple[float, float, float, float]:
        return self.position.x, self.position.y, self.position.x + self.width, self.position.y + self.height


@component
class CircleRenderer:
    surface: pygame.Surface
    position: Position
    radius: float
    color: pygame.Color = "magenta"
    



class MovementProcessor(esper.Processor):
    def process(self):
        for ent, (velocity, position) in esper.get_components(Velocity, Position):
            position.x += velocity.x
            position.y += velocity.y


class ControlledMovementProcessor(esper.Processor):
    def process(self):
        for entity, (velocity) in esper.get_components(Velocity):
            keys = pygame.key.get_pressed()
            if keys[pygame.K_w]:
                velocity.y -= 1
            if keys[pygame.K_s]:
                velocity.y += 1
            if keys[pygame.K_a]:
                velocity.x -= 1
            if keys[pygame.K_d]:
                velocity.x += 1


class RendererProcessor(esper.Processor):
    def process(self):
        for entity, (surface, position, radius, color) in esper.get_components(CircleRenderer):
            pygame.draw.circle(surface, color, position, radius)