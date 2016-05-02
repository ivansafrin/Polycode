

var test = "Testing"

var Rotator = function() {
    
}

Rotator.prototype.init = function(entity) {
    this.entity = entity
}

Rotator.prototype.update = function(elapsed) {
    entity_Roll(this.entity, elapsed * 30.0)
}

new Rotator()