#include "circle.h"

#include <cmath>

#include "engine.h"
#include "hit.h"

constexpr int duration = 10;

Circle::Circle(Sprite& sprite, Vec direction, Actor& defender, int damage)
    : Event{duration},
      sprite{sprite},
      copy{sprite},
      direction{direction},
      defender{defender},
      damage{damage} {
    sprite.center = sprite.size / 2;
    if (direction == Vec{0, 1}) {
        direction = direction * -1;
    } else if (direction == Vec{0, -1}) {
        sprite.shift.y += 8;
    }
}

void Circle::execute(Engine&) {
    if (direction == Vec{0, 1} || direction == Vec{0, -1}) {
        sprite.shift += direction * -2;
    } else {
        sprite.shift += direction * 2;
    }
    sprite.angle += 360 / (duration - 1);
}

void Circle::when_done(Engine& engine) {
    sprite = copy;
    engine.events.add(Hit{defender, damage});
}
