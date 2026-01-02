## Note
These are the first bindings I made for a React component. Needs improvement. Feedback and suggestions are highly welcome.

## Usage

Add as OPAM dependency using pin:

`opam pin reason-react-day-picker git+https://github.com/Software-Deployed/reason-react-day-picker`

Add `reason-react-day-picker` to `libraries` dune stanza:

```
(libraries
 reason-react-day-picker)
```

```ocaml
<DayPicker
  mode="range"
  selected={`Range({
    from: Js.Nullable.return(openDate),
    to_: Js.Nullable.return(closeDate),
  })}
onSelect={`Range(dates => {
  let openDate =
    switch (dates.from->Js.Nullable.toOption) {
    | Some(date) => date
    | None => today
    };
  let closeDate =
    switch (dates.to_->Js.Nullable.toOption) {
    | Some(date) => date
    | None => openDate
    };
  updateOpenDate(openDate);
  updateCloseDate(closeDate);
})}
/>
```
