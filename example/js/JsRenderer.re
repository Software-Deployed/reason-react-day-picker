open SharedFixture;

let config = Scenario.current();

let demoDate =
  Js.Date.make(
    ~year=float_of_int(demoYear),
    ~month=float_of_int(demoMonth),
    ~date=float_of_int(demoDay),
    ~hours=12.0,
    ~minutes=0.0,
    ~seconds=0.0,
    (),
  );

let footer =
  switch (config.footerText) {
  | Some(value) => Some(React.string(value))
  | None => None
  };

let captionLayout = config.captionLayout;
let navLayout = config.navLayout;
let onSelect = `Single((_date: ReactDayPicker.singleDate) => ());
let selected = `Single(Js.Undefined.return(demoDate));

let dayPicker =
  <ReactDayPicker
    mode="single"
    onSelect={onSelect}
    selected={selected}
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

let rendered = ReactDOMServer.renderToString(dayPicker);

let () = print_endline("RENDER_START");
let () = print_endline(rendered);
let () = print_endline("RENDER_END");
