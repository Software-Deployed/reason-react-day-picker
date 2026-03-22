let config = RangeScenario.current();

let selected =
  switch (config.rangeFrom) {
  | Some(from) =>
    switch (config.rangeTo) {
    | Some(to_) =>
      `Range(ReactDayPicker.defined({
        ReactDayPicker.from: ReactDayPicker.defined(from),
        ReactDayPicker.to_: ReactDayPicker.defined(to_),
      }));
    | None =>
      `Range(ReactDayPicker.defined({
        ReactDayPicker.from: ReactDayPicker.defined(from),
        ReactDayPicker.to_: Js.Undefined.fromOption(None),
      }));
    };
  | None =>
    switch (config.rangeTo) {
    | Some(to_) =>
      `Range(ReactDayPicker.defined({
        ReactDayPicker.from: Js.Undefined.fromOption(None),
        ReactDayPicker.to_: ReactDayPicker.defined(to_),
      }));
    | None =>
      `Range(Js.Undefined.fromOption(None));
    };
  };

let onSelect = `Range((_dates: ReactDayPicker.rangeDate) => ());

let root =
  <ReactDayPicker
    mode="range"
    selected={selected}
    onSelect={onSelect}
    showOutsideDays={true}
  />;
