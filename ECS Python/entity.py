import pygame
import esper
from dataclasses import dataclass as component
import singleton

@component
class Position:
    _vector: pygame.math.Vector2 = pygame.math.Vector2(0.0, 0.0)
    _x: float = 0.0
    _y: float = 0.0

    @property
    def x(self):
        return self._x

    @x.setter
    def x(self, value):
        self._x = value


    @property
    def y(self):
        return self._y

    @y.setter
    def y(self, value):
        self._y = value
    

    @property
    def vector(self):
        return pygame.Vector2(self.x, self.y)

    @vector.setter
    def vector(self, value):
        self._y = value.y
        self._x = value.x

    # the dataclass (renamed to component) decorator automatically generates an __init__ function

@component
class Velocity:
    speed: float
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
    radius: float
    color: pygame.Color = pygame.Color(255, 255, 255)


class MovementProcessor(esper.Processor):
    def process(self):
        for entity, (velocity, position) in esper.get_components(Velocity, Position):
            position.x += velocity.x
            position.y += velocity.y


class ControlledMovementProcessor(esper.Processor):
    def process(self):
        for entity, (velocity,) in esper.get_components(Velocity):
            keys = pygame.key.get_pressed()
            direction = pygame.Vector2(0,0)
            if keys[pygame.K_w]:
                direction.y -= 1
            if keys[pygame.K_s]:
                direction.y += 1
            if keys[pygame.K_a]:
                direction.x -= 1
            if keys[pygame.K_d]:
                direction.x += 1
            if direction:
                direction = direction.normalize()
            velocity.x = direction.x * velocity.speed * singleton.delta
            velocity.y = direction.y * velocity.speed * singleton.delta


class RendererProcessor(esper.Processor):
    def process(self):
        for entity, (circle, position) in esper.get_components(CircleRenderer, Position):
            pygame.draw.circle(circle.surface, circle.color, position.vector, circle.radius)