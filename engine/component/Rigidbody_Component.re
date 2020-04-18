let create = (~state: Shared.state, ~rigidbodyType, ~size) : Shared.rigidbody => {
  rigidbodyType,
  size,
  isClicked: false,
  isHovered: false,
};