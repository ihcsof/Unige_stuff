package progetto2022;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.HashMap;
import java.util.Map;

import progetto2022.parser.BufferedParser;
import progetto2022.parser.BufferedTokenizer;
import progetto2022.parser.ParserException;
import progetto2022.parser.ast.Prog;
import progetto2022.visitors.execution.Execute;
import progetto2022.visitors.execution.InterpreterException;
import progetto2022.visitors.typechecking.Typecheck;
import progetto2022.visitors.typechecking.TypecheckerException;

public class Main {

	// instance variables for managing options
	private static final String INPUT_OPT = "-i";
	private static final String OUTPUT_OPT = "-o";
	private static final String NO_TYPE_CHECK = "-ntc";

	/*
	 * maps options to their string values, if any options with no argument are
	 * initialized with null and set with array of length 0 options with argument
	 * are initialized with an array of length 1 containing null
	 */
	public static final Map<String, String[]> options = new HashMap<>();
	static {
		options.put(INPUT_OPT, new String[1]); // one argument, initially null
		options.put(OUTPUT_OPT, new String[1]); // one argument, initially null
		options.put(NO_TYPE_CHECK, null); // no arguments
	}

	// manage generic option errors
	private static void error(String msg) {
		System.err.println(msg);
		System.exit(1);
	}

	// processes all options and their arguments, if any
	private static void processArgs(String[] args) {
		for (var i = 0; i < args.length; i++) {
			var opt = args[i];
			if (!options.containsKey(opt))
				error("Option error.\nValid options:\n\t-i <input>\n\t-ntc");
			var val = options.get(opt);
			if (val == null) // set option with no argument (flag)
				options.put(opt, new String[0]);
			else if (val.length > 0) // one argument expected
			{
				if (i + 1 == args.length)
					error("Missing argument for option " + opt);
				val[0] = args[++i];
			}
		}
	}

	// end of utility methods for option processing

	// opens the input stream, standard input if -i option is null
	private static BufferedReader tryOpenInput(String inputPath) throws FileNotFoundException {
		return new BufferedReader(inputPath == null ? new InputStreamReader(System.in) : new FileReader(inputPath));
	}

	// opens the output stream, standard output if -o option is null
	private static PrintWriter tryOpenOutput(String outputPath) throws FileNotFoundException {
		return outputPath == null ? new PrintWriter(System.out) : new PrintWriter(outputPath);
	}

	public static void main(String[] args) {
		processArgs(args);
		try (var rd = tryOpenInput(options.get(INPUT_OPT)[0]);
				var tokenizer = new BufferedTokenizer(rd);
				var parser = new BufferedParser(tokenizer);
				var pw = tryOpenOutput(options.get(OUTPUT_OPT)[0]);) {
			var prog = parser.parseProg();
			if (options.get(NO_TYPE_CHECK) == null)
				prog.accept(new Typecheck());
			prog.accept(new Execute(pw));
		} catch (IOException e) {
			error("I/O error: " + e.getMessage());
		} catch (ParserException e) {
			error("Syntax error: " + e.getMessage());
		} catch (TypecheckerException e) {
			error("Static error: " + e.getMessage());
		} catch (InterpreterException e) {
			error("Dynamic error: " + e.getMessage());
		}catch (Throwable e) {
			e.printStackTrace();
			error("Unexpected error.");
		}
	}

}
