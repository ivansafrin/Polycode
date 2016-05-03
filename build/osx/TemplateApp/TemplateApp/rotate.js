
function Rotator() {
    
    this.props = [
        {name: "target", label: "Target entity", type: "Entity"},
        {name: "speed", label: "Rotation speed", type: "Number"}
    ]
    
    this.init = function(entity) {
        this.entity = entity
    }
    
    this.update = function(elapsed) {
        entity_Roll(this.entity, elapsed * 30.0)
        //this.entity.Roll(elapsed * 30.0)
    }
}

Rotator