type captionLayout = [
  | `Label
  | `Dropdown
  | `DropdownMonths
  | `DropdownYears
];

type navLayout = [
  | `Around
  | `After
];

type config = {
  name: string,
  captionLayout: option(captionLayout),
  reverseYears: bool,
  navLayout: option(navLayout),
  disableNavigation: bool,
  hideNavigation: bool,
  animate: bool,
  fixedWeeks: bool,
  footerText: option(string),
  hideWeekdays: bool,
  numberOfMonths: int,
  reverseMonths: bool,
  pagedNavigation: bool,
  showOutsideDays: bool,
  showWeekNumber: bool,
};

let all = [|
  "default",
  "outside-hidden",
  "multi-months",
  "reverse-months",
  "nav-after",
  "disable-navigation",
  "hide-navigation",
  "fixed-weeks",
  "animate",
  "caption-dropdown",
  "caption-dropdown-months",
  "caption-dropdown-years",
  "reverse-years",
  "paged-navigation",
|];

let base = {
  name: "default",
  captionLayout: None,
  reverseYears: false,
  navLayout: None,
  disableNavigation: false,
  hideNavigation: false,
  animate: false,
  fixedWeeks: false,
  footerText: Some("Shared native/js sample"),
  hideWeekdays: false,
  numberOfMonths: 1,
  reverseMonths: false,
  pagedNavigation: false,
  showOutsideDays: true,
  showWeekNumber: true,
};

let byName = (name: string): config =>
  switch (name) {
  | "outside-hidden" => {...base, name, showOutsideDays: false}
  | "multi-months" => {...base, name, numberOfMonths: 2}
  | "reverse-months" => {...base, name, numberOfMonths: 2, reverseMonths: true}
  | "nav-after" => {...base, name, navLayout: Some(`After)}
  | "disable-navigation" => {...base, name, disableNavigation: true}
  | "hide-navigation" => {...base, name, hideNavigation: true}
  | "fixed-weeks" => {...base, name, fixedWeeks: true, showOutsideDays: false}
  | "animate" => {...base, name, animate: true}
  | "caption-dropdown" => {...base, name, captionLayout: Some(`Dropdown), showOutsideDays: false, showWeekNumber: false}
  | "caption-dropdown-months" => {...base, name, captionLayout: Some(`DropdownMonths), showOutsideDays: false, showWeekNumber: false}
  | "caption-dropdown-years" => {...base, name, captionLayout: Some(`DropdownYears), showOutsideDays: false, showWeekNumber: false}
  | "reverse-years" => {...base, name, captionLayout: Some(`DropdownYears), reverseYears: true, showOutsideDays: false, showWeekNumber: false}
  | "paged-navigation" => {...base, name, numberOfMonths: 2, pagedNavigation: true}
  | _ => base
  };

let current = (): config => {
  let name =
    if (Array.length(Sys.argv) > 1) {
      let candidate = Sys.argv[Array.length(Sys.argv) - 1];
      if (Array.exists((value) => value == candidate, all)) {
        candidate;
      } else {
        "default";
      };
    } else {
      "default";
    };
  byName(name);
};
