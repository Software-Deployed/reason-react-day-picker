# Example App

This folder follows the same split used by `server-reason-react` demos:

- `example/shared/`: fixture values shared by both targets
- `example/js/`: Melange renderer using `ReactDOMServer.renderToString`
- `example/native/`: native renderer using `ReactDOM.renderToString`

Both renderers use the same props and should produce matching HTML for the same
fixture values in `example/shared/SharedFixture.re`, including `footer` via
`React.string(...)`.

### Run the native renderer

```bash
dune exec ./example/native/NativeRenderer.exe
```

### Run the Melange renderer

The JS renderer is emitted by Melange and executed with Node. Runtime execution
needs the npm packages used by the binding:

```bash
npm install react react-dom react-day-picker
dune build example/js/render/example/js/JsRenderer.re.js
node _build/default/example/js/render/example/js/JsRenderer.re.js
```

### Compare outputs

```bash
dune exec ./example/native/NativeRenderer.exe > /tmp/native.txt
dune build example/js/render/example/js/JsRenderer.re.js
node _build/default/example/js/render/example/js/JsRenderer.re.js > /tmp/js.txt
diff -u /tmp/native.txt /tmp/js.txt
```

Both files include `RENDER_START` / `RENDER_END` markers so you can diff the
HTML section directly.

### Run all parity scenarios

```bash
npm install react react-dom react-day-picker
./example/check-parity.sh
```

To run a subset:

```bash
./example/check-parity.sh default nav-after animate
```
