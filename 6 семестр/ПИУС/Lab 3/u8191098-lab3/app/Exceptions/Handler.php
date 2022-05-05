<?php

namespace App\Exceptions;

use App\Http\ApiV1\Resources\ErrorResource;
use App\Models\Error;
use Illuminate\Validation\ValidationException;
use Illuminate\Database\Eloquent\ModelNotFoundException;
use Illuminate\Foundation\Exceptions\Handler as ExceptionHandler;
use Symfony\Component\HttpKernel\Exception\NotFoundHttpException;
use Symfony\Component\HttpKernel\Exception\UnprocessableEntityHttpException;
use Throwable;
use TypeError;

class Handler extends ExceptionHandler
{
    /**
     * A list of the exception types that are not reported.
     *
     * @var array<int, class-string<Throwable>>
     */
    protected $dontReport = [
        //
    ];

    /**
     * A list of the inputs that are never flashed for validation exceptions.
     *
     * @var array<int, string>
     */
    protected $dontFlash = [
        'current_password',
        'password',
        'password_confirmation',
    ];

    /**
     * Register the exception handling callbacks for the application.
     *
     * @return void
     */
    public function register()
    {
        $this->reportable(function (Throwable $e) {
            //
        });
    }

    public function render($request, Throwable $e)
    {
        $error = new Error(404, 'Not Found');
        if ($e instanceof NotFoundHttpException) {
            return response()->json(new ErrorResource($error), $error->code);
        }

        if ($request->is('api/v1/*')) {
            if ($e instanceof ModelNotFoundException) {
                return response()->json(new ErrorResource($error), $error->code);
            }
            if ($e instanceof ValidationException || $e instanceof TypeError) {
                $error->code = 400;
                $error->message = "Bad Request";
                return response()->json(new ErrorResource($error), $error->code);
            }
            $error->code = 500;
            $error->message = "Internal Server Error";
            return response()->json(new ErrorResource($error), $error->code);
        }
        return parent::render($request, $e);
    }
}
