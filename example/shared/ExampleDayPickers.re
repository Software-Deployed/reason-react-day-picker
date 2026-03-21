let config = Scenario.current();

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

let today = Js.Date.make();
let openDate = today;
let closeDate = Js.Date.make(
  ~year=Js.Date.getFullYear(today),
  ~month=Js.Date.getMonth(today),
  ~date=Js.Date.getDate(today) +. 4.0,
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

let renderPicker = (
  ~mode: string,
  ~selected: ReactDayPicker.selected,
  ~onSelect: ReactDayPicker.onSelect,
) =>
  <ReactDayPicker
    mode={mode}
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

let singleDayPicker =
  renderPicker(
    ~mode="single",
    ~selected=`Single(ReactDayPicker.defined(today)),
    ~onSelect=`Single((_date: ReactDayPicker.singleDate) => ()),
  );

let rangeDayPicker = {
  let openDateRef = ref(openDate);
  let closeDateRef = ref(closeDate);
  let setOpenDate = update => openDateRef := update(openDateRef^);
  let setCloseDate = update => closeDateRef := update(closeDateRef^);

  renderPicker(
    ~mode="range",
    ~selected=`Range(ReactDayPicker.defined({
      ReactDayPicker.from: ReactDayPicker.defined(openDate),
      ReactDayPicker.to_: ReactDayPicker.defined(closeDate),
    })),
    ~onSelect=`Range((dates: ReactDayPicker.rangeDate) => {
      switch (Js.Undefined.toOption(dates)) {
      | Some(dates) =>
        let openDate =
          switch (Js.Undefined.toOption(dates.from)) {
          | Some(date) => date
          | None => today
          };
        let closeDate =
          switch (Js.Undefined.toOption(dates.to_)) {
          | Some(date) => date
          | None => openDate
          };
        setOpenDate(_prev => openDate);
        setCloseDate(_prev => closeDate);
      | None =>
        setOpenDate(_prev => today);
        setCloseDate(_prev => today);
      }
    }),
  );
};

let section = (~title: string, picker: React.element) =>
  React.array([|React.string(title), picker|]);

let root =
  React.array([|
    section(~title="single", singleDayPicker),
    section(~title="range", rangeDayPicker),
  |]);
