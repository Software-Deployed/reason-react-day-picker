## Note
These are the first bindings I made for a React component. Needs improvement. Feedback and suggestions are highly welcome.

## Usage

```ocaml
open Reason_react_day_picker;

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
