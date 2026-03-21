open SharedFixture;

let config = Scenario.current();

let demoDate =
  Js.Date.makeWithYMDHMS(
    ~year=float_of_int(demoYear),
    ~month=float_of_int(demoMonth),
    ~date=float_of_int(demoDay),
    ~hours=12.0,
    ~minutes=0.0,
    ~seconds=0.0,
  );

let footer =
  switch (config.footerText) {
  | Some(value) => Some(React.string(value))
  | None => None
  };

let captionLayout = config.captionLayout;
let navLayout = config.navLayout;

let dayPicker =
  ReactDayPickerNative.make(
    ~mode=`Single,
    ~selected=`Single(Js.Undefined.fromOption(Some(demoDate))),
    ~captionLayout?,
    ~reverseYears=config.reverseYears,
    ~navLayout?,
    ~disableNavigation=config.disableNavigation,
    ~hideNavigation=config.hideNavigation,
    ~animate=config.animate,
    ~fixedWeeks=config.fixedWeeks,
    ~footer?,
    ~hideWeekdays=config.hideWeekdays,
    ~numberOfMonths=config.numberOfMonths,
    ~reverseMonths=config.reverseMonths,
    ~pagedNavigation=config.pagedNavigation,
    ~showOutsideDays=config.showOutsideDays,
    ~showWeekNumber=config.showWeekNumber,
    (),
  );

let rendered = ReactDOM.renderToString(dayPicker);

let () = print_endline("RENDER_START");
let () = print_endline(rendered);
let () = print_endline("RENDER_END");
