type fuzzConfig = FuzzGenerator.fuzzConfig;

let captionLayoutFromString = (value: string): option(Scenario.captionLayout) =>
  switch (value) {
  | "Label" => Some(`Label)
  | "Dropdown" => Some(`Dropdown)
  | "DropdownMonths" => Some(`DropdownMonths)
  | "DropdownYears" => Some(`DropdownYears)
  | _ => None
  };

let navLayoutFromString = (value: string): option(Scenario.navLayout) =>
  switch (value) {
  | "Around" => Some(`Around)
  | "After" => Some(`After)
  | _ => None
  };

let renderFuzzConfig = (config: fuzzConfig) => {
  let captionLayout = switch (config.captionLayout) {
    | Some(`Label) => Some(`Label)
    | Some(`Dropdown) => Some(`Dropdown)
    | Some(`DropdownMonths) => Some(`DropdownMonths)
    | Some(`DropdownYears) => Some(`DropdownYears)
    | None => None
  };
  let navLayout = switch (config.navLayout) {
    | Some(`Around) => Some(`Around)
    | Some(`After) => Some(`After)
    | None => None
  };
  let footer =
    switch (config.footerText) {
    | Some(t) => Some(React.string(t))
    | None => None
    };
  
  let selected =
    switch (config.mode) {
    | "single" =>
      let date =
        switch (config.singleDate) {
        | Some(d) => ReactDayPicker.defined(d)
        | None => Js.Undefined.fromOption(None)
        };
      `Single(date);
    | "multiple" =>
      let dates =
        switch (config.multipleDates) {
        | Some(d) => ReactDayPicker.defined(d)
        | None => Js.Undefined.fromOption(None)
        };
      `Multiple(dates);
    | "range" =>
      let range =
        switch (config.rangeFrom) {
        | Some(from) =>
          switch (config.rangeTo) {
          | Some(to_) =>
            ReactDayPicker.defined({
              ReactDayPicker.from: ReactDayPicker.defined(from),
              ReactDayPicker.to_: ReactDayPicker.defined(to_),
            });
          | None => Js.Undefined.fromOption(None)
          };
        | None => Js.Undefined.fromOption(None)
        };
      `Range(range);
    | _ => `Single(Js.Undefined.fromOption(None))
    };
  
  let onSelect =
    switch (config.mode) {
    | "single" => `Single((_date: ReactDayPicker.singleDate) => ())
    | "multiple" => `Multiple((_dates: ReactDayPicker.multipleDate) => ())
    | "range" => `Range((_dates: ReactDayPicker.rangeDate) => ())
    | _ => `Single((_date: ReactDayPicker.singleDate) => ())
    };
  
  <ReactDayPicker
    mode={config.mode}
    selected={selected}
    onSelect={onSelect}
    captionLayout=?captionLayout
    reverseYears=config.reverseYears
    navLayout=?navLayout
    disableNavigation=config.disableNavigation
    hideNavigation=config.hideNavigation
    animate=config.animate
    fixedWeeks=config.fixedWeeks
    footer=?footer
    hideWeekdays=config.hideWeekdays
    numberOfMonths=config.numberOfMonths
    reverseMonths=config.reverseMonths
    pagedNavigation=config.pagedNavigation
    showOutsideDays=config.showOutsideDays
    showWeekNumber=config.showWeekNumber
  />;
};
