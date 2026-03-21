type mode = [
  | `Single
  | `Multiple
  | `Range
];

let modeToString = (v: mode): string =>
  switch (v) {
  | `Single => "single"
  | `Multiple => "multiple"
  | `Range => "range"
  };

type captionLayout = [
  | `Label
  | `Dropdown
  | `DropdownMonths
  | `DropdownYears
];

let captionLayoutToString = (v: captionLayout): string =>
  switch (v) {
  | `Label => "label"
  | `Dropdown => "dropdown"
  | `DropdownMonths => "dropdown-months"
  | `DropdownYears => "dropdown-years"
  };

type navLayout = [
  | `Around
  | `After
];

let navLayoutToString = (v: navLayout): string =>
  switch (v) {
  | `Around => "around"
  | `After => "after"
  };

type reactNode = React.element;

/* `reactNode` can be created with `React.string`, `React.int`, JSX, etc. */

type singleDate = Js.Undefined.t(Js.Date.t);
type multipleDate = Js.Undefined.t(array(Js.Date.t));
type dateRange = {
  from: singleDate,
  [@mel.as "to"] to_: singleDate,
};
type rangeDate = Js.Undefined.t(dateRange);

type selected = [
  | `Single(singleDate)
  | `Multiple(multipleDate)
  | `Range(rangeDate)
];

type onSelect = [
  | `Single(singleDate => unit)
  | `Multiple(multipleDate => unit)
  | `Range(rangeDate => unit)
];

[@mel.obj]
external makeProps:
  (
    ~mode:
      [@mel.string] [
        | [@mel.as "single"] `Single
        | [@mel.as "multiple"] `Multiple
        | [@mel.as "range"] `Range
      ],
    ~onSelect:
      [@mel.unwrap] [
        | `Single(singleDate => unit)
        | `Multiple(multipleDate => unit)
        | `Range(rangeDate => unit)
      ],
    ~selected:
      [@mel.unwrap] [
        | `Single(singleDate)
        | `Multiple(multipleDate)
        | `Range(rangeDate)
      ],
    ~captionLayout:
      [@mel.string] [
        | [@mel.as "label"] `Label
        | [@mel.as "dropdown"] `Dropdown
        | [@mel.as "dropdown-months"] `DropdownMonths
        | [@mel.as "dropdown-years"] `DropdownYears
      ]=?,
    ~reverseYears: bool=?,
    ~navLayout:
      [@mel.string] [
        | [@mel.as "around"] `Around
        | [@mel.as "after"] `After
      ]=?,
    ~disableNavigation: bool=?,
    ~hideNavigation: bool=?,
    ~animate: bool=?,
    ~fixedWeeks: bool=?,
    ~footer: reactNode=?,
    ~hideWeekdays: bool=?,
    ~numberOfMonths: int=?,
    ~reverseMonths: bool=?,
    ~pagedNavigation: bool=?,
    ~showOutsideDays: bool=?,
    ~showWeekNumber: bool=?,
    ~key: string=?,
    unit
  ) =>
  {
    .
    "mode": string,
    "selected": 'selected,
    "onSelect": 'onSelect,
    "captionLayout": string,
    "reverseYears": bool,
    "navLayout": string,
    "disableNavigation": bool,
    "hideNavigation": bool,
    "animate": bool,
    "fixedWeeks": bool,
    "footer": reactNode,
    "hideWeekdays": bool,
    "numberOfMonths": int,
    "reverseMonths": bool,
    "pagedNavigation": bool,
    "showOutsideDays": bool,
    "showWeekNumber": bool,
  };

[@mel.module "react-day-picker"]
external make:
  {
    ..
    "mode": string,
    "onSelect": 'onSelect,
    "selected": 'selected,
    "captionLayout": string,
    "navLayout": string,
    "disableNavigation": bool,
    "hideNavigation": bool,
    "animate": bool,
    "fixedWeeks": bool,
    "footer": reactNode,
    "hideWeekdays": bool,
    "numberOfMonths": int,
    "reverseMonths": bool,
    "pagedNavigation": bool,
    "showOutsideDays": bool,
    "showWeekNumber": bool,
  } =>
  React.element =
  "DayPicker";
