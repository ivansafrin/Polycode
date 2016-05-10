
function Rotator() {
}

Rotator.prototype.init = function(entity) {
    this.entity = entity
}

Rotator.prototype.update = function(elapsed) {
    this.entity.Roll(elapsed * 30.0)
    print(this.entity.getPosition().x)
}

Rotator