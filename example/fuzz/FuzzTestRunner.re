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

let testFuzzConfig = (name, config) =>
  Alcotest.test_case(name, `Quick, () => {
    let _output = runNativeTest(config);
    Alcotest.check(Alcotest.bool)("Native renders successfully", true, true);
  });

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
    testFuzzConfig(
      "range-same-day",
      {
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
      },
    ),
    testFuzzConfig(
      "range-multi-day",
      {
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
      },
    ),
    testFuzzConfig(
      "range-start-only",
      {
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
      },
    ),
    testFuzzConfig(
      "range-end-only",
      {
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
      },
    ),
    testFuzzConfig(
      "range-week-long",
      {
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
      },
    ),
  ];
  
  let singleTests = Array.init(5, i =>
    testFuzzConfig(
      "single-" ++ string_of_int(i),
      FuzzGenerator.generateSingleConfig(~seed=i, ~baseYear, ~baseMonth),
    )
  ) |> Array.to_list;
  
  let multipleTests = Array.init(5, i =>
    testFuzzConfig(
      "multiple-" ++ string_of_int(i),
      FuzzGenerator.generateMultipleConfig(~seed=100+i, ~baseYear, ~baseMonth),
    )
  ) |> Array.to_list;
  
  let randomRangeTests = Array.init(5, i =>
    testFuzzConfig(
      "random-range-" ++ string_of_int(i),
      FuzzGenerator.generateRangeConfig(~seed=200+i, ~baseYear, ~baseMonth),
    )
  ) |> Array.to_list;
  
  Alcotest.run("Fuzz Native Render Tests", [
    ("range-specific", rangeTests),
    ("single-mode", singleTests),
    ("multiple-mode", multipleTests),
    ("range-random", randomRangeTests),
  ]);
};
