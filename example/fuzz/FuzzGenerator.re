type fuzzConfig = {
  name: string,
  mode: string,
  captionLayout: option(Scenario.captionLayout),
  reverseYears: bool,
  navLayout: option(Scenario.navLayout),
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
  singleDate: option(Js.Date.t),
  multipleDates: option(array(Js.Date.t)),
  rangeFrom: option(Js.Date.t),
  rangeTo: option(Js.Date.t),
};

let randomBool = () => Random.int(2) == 0;

let randomInt = (~min, ~max) => min + Random.int(max - min + 1);

let randomOption = (value: 'a) => randomBool() ? Some(value) : None;

let randomCaptionLayout = () =>
  switch (Random.int(4)) {
  | 0 => Some(`Label)
  | 1 => Some(`Dropdown)
  | 2 => Some(`DropdownMonths)
  | 3 => Some(`DropdownYears)
  | _ => None
  };

let randomNavLayout = () =>
  switch (Random.int(3)) {
  | 0 => Some(`Around)
  | 1 => Some(`After)
  | _ => None
  };

let randomDate = (~baseYear, ~baseMonth) => {
  let day = randomInt(~min=1, ~max=28);
  Js.Date.make(
    ~year=float_of_int(baseYear),
    ~month=float_of_int(baseMonth),
    ~date=float_of_int(day),
    ~hours=12.0,
    ~minutes=0.0,
    ~seconds=0.0,
    (),
  );
};

let generateSingleConfig = (~seed, ~baseYear, ~baseMonth): fuzzConfig => {
  Random.init(seed);
  let mode = "single";
  let singleDate =
    if (randomBool()) {
      Some(randomDate(~baseYear, ~baseMonth));
    } else {
      None;
    };
  
  {
    name: "fuzz-single-" ++ string_of_int(seed),
    mode,
    captionLayout: randomCaptionLayout(),
    reverseYears: randomBool(),
    navLayout: randomNavLayout(),
    disableNavigation: randomBool(),
    hideNavigation: randomBool(),
    animate: randomBool(),
    fixedWeeks: randomBool(),
    footerText: if (randomBool()) {Some("Fuzz test")} else {None},
    hideWeekdays: randomBool(),
    numberOfMonths: randomInt(~min=1, ~max=3),
    reverseMonths: randomBool(),
    pagedNavigation: randomBool(),
    showOutsideDays: randomBool(),
    showWeekNumber: randomBool(),
    singleDate,
    multipleDates: None,
    rangeFrom: None,
    rangeTo: None,
  };
};

let generateMultipleConfig = (~seed, ~baseYear, ~baseMonth): fuzzConfig => {
  Random.init(seed);
  let mode = "multiple";
  let count = randomInt(~min=1, ~max=5);
  let multipleDates =
    if (randomBool()) {
      Some(Array.init(count, _ => randomDate(~baseYear, ~baseMonth)));
    } else {
      None;
    };
  
  {
    name: "fuzz-multiple-" ++ string_of_int(seed),
    mode,
    captionLayout: randomCaptionLayout(),
    reverseYears: randomBool(),
    navLayout: randomNavLayout(),
    disableNavigation: randomBool(),
    hideNavigation: randomBool(),
    animate: randomBool(),
    fixedWeeks: randomBool(),
    footerText: if (randomBool()) {Some("Fuzz test")} else {None},
    hideWeekdays: randomBool(),
    numberOfMonths: randomInt(~min=1, ~max=3),
    reverseMonths: randomBool(),
    pagedNavigation: randomBool(),
    showOutsideDays: randomBool(),
    showWeekNumber: randomBool(),
    singleDate: None,
    multipleDates,
    rangeFrom: None,
    rangeTo: None,
  };
};

let generateRangeConfig = (~seed, ~baseYear, ~baseMonth): fuzzConfig => {
  Random.init(seed);
  let mode = "range";
  let hasRange = randomBool();
  let rangeFrom = hasRange ? Some(randomDate(~baseYear, ~baseMonth)) : None;
  let rangeTo =
    switch (rangeFrom) {
    | Some(from) =>
      let fromDay = Js.Date.getDate(from);
      let toDay = fromDay +. float_of_int(randomInt(~min=0, ~max=14));
      Some(Js.Date.make(
        ~year=Js.Date.getFullYear(from),
        ~month=Js.Date.getMonth(from),
        ~date=toDay,
        ~hours=12.0,
        ~minutes=0.0,
        ~seconds=0.0,
        (),
      ));
    | None => None
    };
  
  {
    name: "fuzz-range-" ++ string_of_int(seed),
    mode,
    captionLayout: randomCaptionLayout(),
    reverseYears: randomBool(),
    navLayout: randomNavLayout(),
    disableNavigation: randomBool(),
    hideNavigation: randomBool(),
    animate: randomBool(),
    fixedWeeks: randomBool(),
    footerText: if (randomBool()) {Some("Fuzz test")} else {None},
    hideWeekdays: randomBool(),
    numberOfMonths: randomInt(~min=1, ~max=3),
    reverseMonths: randomBool(),
    pagedNavigation: randomBool(),
    showOutsideDays: randomBool(),
    showWeekNumber: randomBool(),
    singleDate: None,
    multipleDates: None,
    rangeFrom,
    rangeTo,
  };
};

let generateConfig = (~seed, ~baseYear, ~baseMonth): fuzzConfig => {
  let modeType = Random.int(3);
  switch (modeType) {
  | 0 => generateSingleConfig(~seed, ~baseYear, ~baseMonth)
  | 1 => generateMultipleConfig(~seed, ~baseYear, ~baseMonth)
  | _ => generateRangeConfig(~seed, ~baseYear, ~baseMonth)
  };
};
