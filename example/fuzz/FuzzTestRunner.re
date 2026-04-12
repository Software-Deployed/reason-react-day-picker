let normalizeHtml = (html: string): string => {
  html
  |> String.trim
  |> String.split_on_char('\n')
  |> List.map(String.trim)
  |> String.concat("")
};

let renderNative = (config: FuzzGenerator.fuzzConfig): string => {
  let element = FuzzRenderer.renderFuzzConfig(config);
  ReactDOM.renderToString(element);
};

let runNativeTest = (config: FuzzGenerator.fuzzConfig) => {
  let nativeOutput = renderNative(config);
  normalizeHtml(nativeOutput);
};

let makeDate = (~year: int, ~month: int, ~day: int): Js.Date.t =>
  Js.Date.make(
    ~year=float_of_int(year),
    ~month=float_of_int(month),
    ~date=float_of_int(day),
    ~hours=12.0,
    ~minutes=0.0,
    ~seconds=0.0,
    (),
  );

let () = {
  let baseYear = 2026;
  let baseMonth = 2;
  let today = makeDate(~year=baseYear, ~month=baseMonth, ~day=21);
  let tomorrow = makeDate(~year=baseYear, ~month=baseMonth, ~day=22);
  let nextWeek = makeDate(~year=baseYear, ~month=baseMonth, ~day=28);

  let rangeTests = [
    Alcobar.test_case(
      "range-same-day",
      [Alcobar.const(())],
      () => {
        let config = {
          FuzzGenerator.name: "range-same-day",
          mode: "range",
          captionLayout: None,
          reverseYears: false,
          navLayout: None,
          disableNavigation: false,
          hideNavigation: false,
          animate: false,
          fixedWeeks: false,
          footerText: None,
          hideWeekdays: false,
          numberOfMonths: 1,
          reverseMonths: false,
          pagedNavigation: false,
          showOutsideDays: true,
          showWeekNumber: false,
          singleDate: None,
          multipleDates: None,
          rangeFrom: Some(today),
          rangeTo: Some(today),
        };
        ignore(runNativeTest(config));
      },
    ),
    Alcobar.test_case(
      "range-multi-day",
      [Alcobar.const(())],
      () => {
        let config = {
          FuzzGenerator.name: "range-multi-day",
          mode: "range",
          captionLayout: None,
          reverseYears: false,
          navLayout: None,
          disableNavigation: false,
          hideNavigation: false,
          animate: false,
          fixedWeeks: false,
          footerText: None,
          hideWeekdays: false,
          numberOfMonths: 1,
          reverseMonths: false,
          pagedNavigation: false,
          showOutsideDays: true,
          showWeekNumber: false,
          singleDate: None,
          multipleDates: None,
          rangeFrom: Some(today),
          rangeTo: Some(tomorrow),
        };
        ignore(runNativeTest(config));
      },
    ),
    Alcobar.test_case(
      "range-start-only",
      [Alcobar.const(())],
      () => {
        let config = {
          FuzzGenerator.name: "range-start-only",
          mode: "range",
          captionLayout: None,
          reverseYears: false,
          navLayout: None,
          disableNavigation: false,
          hideNavigation: false,
          animate: false,
          fixedWeeks: false,
          footerText: None,
          hideWeekdays: false,
          numberOfMonths: 1,
          reverseMonths: false,
          pagedNavigation: false,
          showOutsideDays: true,
          showWeekNumber: false,
          singleDate: None,
          multipleDates: None,
          rangeFrom: Some(today),
          rangeTo: None,
        };
        ignore(runNativeTest(config));
      },
    ),
    Alcobar.test_case(
      "range-end-only",
      [Alcobar.const(())],
      () => {
        let config = {
          FuzzGenerator.name: "range-end-only",
          mode: "range",
          captionLayout: None,
          reverseYears: false,
          navLayout: None,
          disableNavigation: false,
          hideNavigation: false,
          animate: false,
          fixedWeeks: false,
          footerText: None,
          hideWeekdays: false,
          numberOfMonths: 1,
          reverseMonths: false,
          pagedNavigation: false,
          showOutsideDays: true,
          showWeekNumber: false,
          singleDate: None,
          multipleDates: None,
          rangeFrom: None,
          rangeTo: Some(today),
        };
        ignore(runNativeTest(config));
      },
    ),
    Alcobar.test_case(
      "range-week-long",
      [Alcobar.const(())],
      () => {
        let config = {
          FuzzGenerator.name: "range-week-long",
          mode: "range",
          captionLayout: None,
          reverseYears: false,
          navLayout: None,
          disableNavigation: false,
          hideNavigation: false,
          animate: false,
          fixedWeeks: false,
          footerText: None,
          hideWeekdays: false,
          numberOfMonths: 1,
          reverseMonths: false,
          pagedNavigation: false,
          showOutsideDays: true,
          showWeekNumber: false,
          singleDate: None,
          multipleDates: None,
          rangeFrom: Some(today),
          rangeTo: Some(nextWeek),
        };
        ignore(runNativeTest(config));
      },
    ),
  ];

  let singleTests = [
    Alcobar.test_case(
      "fuzz-single",
      [FuzzGenerator.singleConfigGen(~baseYear, ~baseMonth)],
      config => {
        ignore(runNativeTest(config));
      },
    ),
  ];

  let multipleTests = [
    Alcobar.test_case(
      "fuzz-multiple",
      [FuzzGenerator.multipleConfigGen(~baseYear, ~baseMonth)],
      config => {
        ignore(runNativeTest(config));
      },
    ),
  ];

  let rangeRandomTests = [
    Alcobar.test_case(
      "fuzz-range",
      [FuzzGenerator.rangeConfigGen(~baseYear, ~baseMonth)],
      config => {
        ignore(runNativeTest(config));
      },
    ),
  ];

  Alcobar.run("Fuzz Native Render Tests", [
    ("range-specific", rangeTests),
    ("single-mode", singleTests),
    ("multiple-mode", multipleTests),
    ("range-random", rangeRandomTests),
  ]);
};
