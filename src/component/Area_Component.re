// let create =
//     (
//       ~entity: Belt.Map.String.key,
//       ~state: Type.gameState,
//       ~areaType: Type.areaType,
//       ()
//     ) : Type.gameState => {
//   ...state,
//   area: Belt.Map.String.set(state.area, entity, {
//     areaType,
//     size: 1.0
//   }),
// };