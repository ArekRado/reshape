// let create =
//     (
//       ~id: Belt.Map.String.key,
//       ~isPlaying=?,
//       ~keyframes: Belt.List.t(Shared.keyframe(Vector_Util.t)),
//       ~entity: string,
//       ~state: Shared.state,
//       ~wrapMode=?,
//       (),
//     )
//     : Shared.state => {
//   ...state,
//   animationVector:
//     Belt.Map.String.set(
//       state.animationVector,
//       id,
//       {
//         entity,
//         name: Uuid_Util.humanFriendlyEntity(id),
//         keyframes: mapParamToKeyframes(keyframes),
//         isPlaying:
//           switch (isPlaying) {
//           | None => false
//           | Some(v) => v
//           },
//         wrapMode: switch (wrapMode) {
//           | None => Once
//           | Some(v) => v
//           },
//         currentTime: 0.0,
//         value: Vector_Util.zero,
//         isFinished: false,
//       },
//     ),
// };