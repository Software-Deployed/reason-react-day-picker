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

let optionGen = gen =>
  Alcobar.choose([
    Alcobar.const(None),
    Alcobar.map([gen], v => Some(v)),
  ]);

let captionLayoutGen =
  Alcobar.choose([
    Alcobar.const(None),
    Alcobar.const(Some(`Label)),
    Alcobar.const(Some(`Dropdown)),
    Alcobar.const(Some(`DropdownMonths)),
    Alcobar.const(Some(`DropdownYears)),
  ]);

let navLayoutGen =
  Alcobar.choose([
    Alcobar.const(None),
    Alcobar.const(Some(`Around)),
    Alcobar.const(Some(`After)),
  ]);

let rangeGen = (~min: int, ~max: int) =>
  Alcobar.map([Alcobar.range(max - min + 1)], n => min + n);

let dateGen = (~baseYear: int, ~baseMonth: int) =>
  Alcobar.map([rangeGen(~min=1, ~max=28)], day =>
    Js.Date.make(
      ~year=float_of_int(baseYear),
      ~month=float_of_int(baseMonth),
      ~date=float_of_int(day),
      ~hours=12.0,
      ~minutes=0.0,
      ~seconds=0.0,
      (),
    )
  );

let singleConfigGen = (~baseYear: int, ~baseMonth: int): Alcobar.gen(fuzzConfig) =>
  Alcobar.map([
    Alcobar.const("single"),
    captionLayoutGen,
    Alcobar.bool,
    navLayoutGen,
    Alcobar.bool,
    Alcobar.bool,
    Alcobar.bool,
    Alcobar.bool,
    optionGen(Alcobar.const("Fuzz test")),
    Alcobar.bool,
    rangeGen(~min=1, ~max=3),
    Alcobar.bool,
    Alcobar.bool,
    Alcobar.bool,
    Alcobar.bool,
    optionGen(dateGen(~baseYear, ~baseMonth)),
    Alcobar.const(None),
    Alcobar.const(None),
    Alcobar.const(None),
  ], (
    mode,
    captionLayout,
    reverseYears,
    navLayout,
    disableNavigation,
    hideNavigation,
    animate,
    fixedWeeks,
    footerText,
    hideWeekdays,
    numberOfMonths,
    reverseMonths,
    pagedNavigation,
    showOutsideDays,
    showWeekNumber,
    singleDate,
    multipleDates,
    rangeFrom,
    rangeTo,
  ) => {
    name: "fuzz-single",
    mode,
    captionLayout,
    reverseYears,
    navLayout,
    disableNavigation,
    hideNavigation,
    animate,
    fixedWeeks,
    footerText,
    hideWeekdays,
    numberOfMonths,
    reverseMonths,
    pagedNavigation,
    showOutsideDays,
    showWeekNumber,
    singleDate,
    multipleDates,
    rangeFrom,
    rangeTo,
  });

let multipleConfigGen = (~baseYear: int, ~baseMonth: int): Alcobar.gen(fuzzConfig) =>
  Alcobar.map([
    Alcobar.const("multiple"),
    captionLayoutGen,
    Alcobar.bool,
    navLayoutGen,
    Alcobar.bool,
    Alcobar.bool,
    Alcobar.bool,
    Alcobar.bool,
    optionGen(Alcobar.const("Fuzz test")),
    Alcobar.bool,
    rangeGen(~min=1, ~max=3),
    Alcobar.bool,
    Alcobar.bool,
    Alcobar.bool,
    Alcobar.bool,
    Alcobar.const(None),
    optionGen(Alcobar.array(dateGen(~baseYear, ~baseMonth))),
    Alcobar.const(None),
    Alcobar.const(None),
  ], (
    mode,
    captionLayout,
    reverseYears,
    navLayout,
    disableNavigation,
    hideNavigation,
    animate,
    fixedWeeks,
    footerText,
    hideWeekdays,
    numberOfMonths,
    reverseMonths,
    pagedNavigation,
    showOutsideDays,
    showWeekNumber,
    singleDate,
    multipleDates,
    rangeFrom,
    rangeTo,
  ) => {
    name: "fuzz-multiple",
    mode,
    captionLayout,
    reverseYears,
    navLayout,
    disableNavigation,
    hideNavigation,
    animate,
    fixedWeeks,
    footerText,
    hideWeekdays,
    numberOfMonths,
    reverseMonths,
    pagedNavigation,
    showOutsideDays,
    showWeekNumber,
    singleDate,
    multipleDates,
    rangeFrom,
    rangeTo,
  });

let rangePairGen = (~baseYear: int, ~baseMonth: int) =>
  Alcobar.choose([
    Alcobar.const((None, None)),
    Alcobar.map([
      dateGen(~baseYear, ~baseMonth),
      rangeGen(~min=0, ~max=14),
    ], (from, offset) => {
      let fromDay = int_of_float(Js.Date.getDate(from));
      let toDay = float_of_int(fromDay + offset);
      (
        Some(from),
        Some(
          Js.Date.make(
            ~year=Js.Date.getFullYear(from),
            ~month=Js.Date.getMonth(from),
            ~date=toDay,
            ~hours=12.0,
            ~minutes=0.0,
            ~seconds=0.0,
            (),
          ),
        ),
      );
    }),
  ]);

let rangeConfigGen = (~baseYear: int, ~baseMonth: int): Alcobar.gen(fuzzConfig) =>
  Alcobar.map([
    Alcobar.const("range"),
    rangePairGen(~baseYear, ~baseMonth),
    captionLayoutGen,
    Alcobar.bool,
    navLayoutGen,
    Alcobar.bool,
    Alcobar.bool,
    Alcobar.bool,
    Alcobar.bool,
    optionGen(Alcobar.const("Fuzz test")),
    Alcobar.bool,
    rangeGen(~min=1, ~max=3),
    Alcobar.bool,
    Alcobar.bool,
    Alcobar.bool,
    Alcobar.bool,
    Alcobar.const(None),
    Alcobar.const(None),
  ], (
    mode,
    (rangeFrom, rangeTo),
    captionLayout,
    reverseYears,
    navLayout,
    disableNavigation,
    hideNavigation,
    animate,
    fixedWeeks,
    footerText,
    hideWeekdays,
    numberOfMonths,
    reverseMonths,
    pagedNavigation,
    showOutsideDays,
    showWeekNumber,
    singleDate,
    multipleDates,
  ) => {
    name: "fuzz-range",
    mode,
    captionLayout,
    reverseYears,
    navLayout,
    disableNavigation,
    hideNavigation,
    animate,
    fixedWeeks,
    footerText,
    hideWeekdays,
    numberOfMonths,
    reverseMonths,
    pagedNavigation,
    showOutsideDays,
    showWeekNumber,
    singleDate,
    multipleDates,
    rangeFrom,
    rangeTo,
  });

let configGen = (~baseYear: int, ~baseMonth: int): Alcobar.gen(fuzzConfig) =>
  Alcobar.choose([
    singleConfigGen(~baseYear, ~baseMonth),
    multipleConfigGen(~baseYear, ~baseMonth),
    rangeConfigGen(~baseYear, ~baseMonth),
  ]);
