[@mel.scope "document"]
external getElementById: string => Js.Nullable.t('a) = "getElementById";

[@mel.module "react-dom"]
external render: (React.element, 'a) => unit = "render";

let rootElement =
  switch (Js.Nullable.toOption(getElementById("root"))) {
  | Some(el) => el
  | None =>
    failwith("Root element not found")
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

let today = makeDate(~year=2026, ~month=2, ~day=21);
let openDate = today;
let closeDate = makeDate(~year=2026, ~month=2, ~day=25);

let footer = Some(React.string("Browser test sample"));

let singleDayPicker =
  <ReactDayPicker
    mode="single"
    selected={`Single(Js.Undefined.return(today))}
    onSelect={`Single((_date: ReactDayPicker.singleDate) => ())}
    footer=?footer
    showOutsideDays={true}
    showWeekNumber={true}
  />;

let rangeDayPicker = {
  let openDateRef = ref(openDate);
  let closeDateRef = ref(closeDate);
  let setOpenDate = update => openDateRef := update(openDateRef^);
  let setCloseDate = update => closeDateRef := update(closeDateRef^);

  <ReactDayPicker
    mode="range"
    selected={`Range(Js.Undefined.return({
      ReactDayPicker.from: Js.Undefined.return(openDate),
      ReactDayPicker.to_: Js.Undefined.return(closeDate),
    }))}
    onSelect={`Range((dates: ReactDayPicker.rangeDate) => {
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
    })}
    footer=?footer
    showOutsideDays={true}
    showWeekNumber={true}
  />;
};

let root =
  React.array([|
    React.string("single picker"),
    singleDayPicker,
    React.string("range picker"),
    rangeDayPicker,
  |]);

let () = render(root, rootElement);
