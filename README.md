## Note
These are the first bindings I made for a React component. Needs improvement. Feedback and suggestions are highly welcome.

## Installation

### Melange (Browser/Client)

Add as OPAM dependency using pin:

`opam pin reason-react-day-picker git+https://github.com/Software-Deployed/reason-react-day-picker`

Add `reason-react-day-picker` to `libraries` dune stanza:

```lisp
(libraries
 reason-react-day-picker)
```

### Native (Server-Side Rendering)

The native version is optional and only builds when `server-reason-react` is installed.

1. Install server-reason-react:
```bash
opam install server-reason-react
```

2. Add `reason-react-day-picker.native` to your libraries:
```lisp
(libraries
 reason-react-day-picker.native)
```

## Usage

### Melange (Browser)

```ocaml
let props =
  ReactDayPicker.makeProps(
    ~mode=`Range,
    ~selected=`Range(Js.Undefined.return({
      ReactDayPicker.from: Js.Undefined.return(openDate),
      ReactDayPicker.to_: Js.Undefined.return(closeDate),
    })),
    ~onSelect=`Range((dates: ReactDayPicker.rangeDate) => {
      switch (dates->Js.Undefined.toOption) {
      | Some(dates) =>
        let openDate =
          switch (dates.from->Js.Undefined.toOption) {
          | Some(date) => date
          | None => today
          };
        let closeDate =
          switch (dates.to_->Js.Undefined.toOption) {
          | Some(date) => date
          | None => openDate
          };
        updateOpenDate(openDate);
        updateCloseDate(closeDate);
      | None =>
        updateOpenDate(today);
        updateCloseDate(today);
      };
    }),
    (),
  );

let calendar = React.createElement(ReactDayPicker.make, props);
```

### Native (Server-Side Rendering)

```reason
let today = Js.Date.make();

let calendar =
  ReactDayPickerNative.make(
    ~mode=`Single,
    ~selected=`Single(Some(today)),
    ~numberOfMonths=1,
    ~showOutsideDays=true,
    (),
  );

/* Render to HTML string */
let html = ReactDOM.renderToString(calendar);
```

### Example parity check

This repo includes a small universal example in `example/` that mirrors the
layout used by `server-reason-react` demos:

```bash
dune exec ./example/native/NativeRenderer.exe
dune build example/js/render/example/js/JsRenderer.re.js
node _build/default/example/js/render/example/js/JsRenderer.re.js
```

The Melange renderer needs `react`, `react-dom`, and `react-day-picker`
installed in `node_modules` to run under Node.

#### Native Props

The native implementation supports the following props:

| Prop | Type | Description |
|------|------|-------------|
| `mode` | `option(mode)` | Selection mode using `` `Single ``, `` `Multiple ``, or `` `Range `` |
| `selected` | `option(selected)` | Selected date(s) |
| `captionLayout` | `option(captionLayout)` | Caption layout using typed constructors |
| `navLayout` | `option(navLayout)` | Navigation layout using typed constructors |
| `numberOfMonths` | `option(int)` | Number of months to display (default: 1) |
| `showOutsideDays` | `option(bool)` | Show days from previous/next months (default: false) |
| `showWeekNumber` | `option(bool)` | Show week numbers (default: false) |
| `hideWeekdays` | `option(bool)` | Hide weekday header row (default: false) |
| `footer` | `option(React.element)` | Footer content |

#### Selection Types

```reason
type mode = [
  | `Single
  | `Multiple
  | `Range
];

type captionLayout = [
  | `Label
  | `Dropdown
  | `DropdownMonths
  | `DropdownYears
];

type navLayout = [
  | `Around
  | `After
];

type selected = [
  | `Single(Js.Date.t option)
  | `Multiple(array(Js.Date.t) option)
  | `Range(dateRange option)
];

type dateRange = {
  from: Js.Date.t option,
  to_: Js.Date.t option,
};

type reactNode = React.element;
```

For text footers, pass `React.string("...")`.

#### Styling

The native output uses the same CSS classes as react-day-picker. Include the CSS from the NPM package or use your own styles:

```css
/* Include react-day-picker styles */
@import "react-day-picker/style.css";
```

Or use the `rdp-*` class names to create custom styles.

## HTML Output Structure

The native component renders this HTML structure:

```html
<div class="rdp-root" role="application">
  <div class="rdp-months">
    <div class="rdp-month">
      <div class="rdp-month_caption">
        <span class="rdp-caption_label">January 2026</span>
      </div>
      <table class="rdp-month_grid" role="grid">
        <thead>
          <tr>
            <th class="rdp-weekday">Su</th>
            <!-- ... more weekdays -->
          </tr>
        </thead>
        <tbody class="rdp-weeks">
          <tr class="rdp-week">
             <td class="rdp-day rdp-outside">28</td>
            <!-- ... more days -->
             <td class="rdp-day rdp-today rdp-selected">15</td>
          </tr>
        </tbody>
      </table>
    </div>
  </div>
  <div class="rdp-footer">Footer content</div>
</div>
```

## CSS Classes

| Class | Description |
|-------|-------------|
| `rdp-root` | Root container |
| `rdp-months` | Months wrapper |
| `rdp-month` | Single month container |
| `rdp-month_caption` | Month caption (title) |
| `rdp-caption_label` | Month/year label |
| `rdp-month_grid` | Calendar table |
| `rdp-weekday` | Weekday header cell |
| `rdp-weeks` | Table body |
| `rdp-week` | Week row |
| `rdp-day` | Day cell |
| `rdp-today` | Today's date |
| `rdp-selected` | Selected date |
| `rdp-outside` | Day outside current month |
| `rdp-range_start` | Range selection start |
| `rdp-range_middle` | Range selection middle |
| `rdp-range_end` | Range selection end |
| `rdp-week_number` | Week number cell |
| `rdp-footer` | Footer container |

## License

MIT
